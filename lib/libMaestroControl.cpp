#include "libMaestroControl.h"
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <csignal>


using namespace std;

#ifdef _WIN32
#define O_NOCTTY 0

#include <windows.h>

#else
#endif
int pos_j = 4000;
int pos_i = 4000;
bool exits = false;
bool force_exit = false;
char *null = nullptr;

MaestroControl::MaestroControl(const char *dev) {
    device = dev;
    fd = open(device, O_RDWR | O_NOCTTY);
}


void MaestroControl::reconnect() {
    fd = open(device, O_RDWR | O_NOCTTY);
    // perror("Reconnecting");
}


std::string MaestroControl::getSerialPort() {
    std::ostringstream buffer;
    buffer << device;
    return buffer.str();
}


int MaestroControl::setPosition(unsigned char channel, unsigned short target) {
    unsigned char command[] = {0x84, channel, static_cast<unsigned char>(target & 0x7F),
                               static_cast<unsigned char>(target >> 7 & 0x7F)};
    if (write(fd, command, sizeof(command)) == -1) {
        reconnect();
        perror("Error writing");
        return -1;
    }
    return 0;
}


int MaestroControl::getPosition(unsigned char channel) {
    unsigned char command[] = {0x90, channel};
    if (write(fd, command, sizeof(command)) == -1) {
        reconnect();
        perror("Error writing");
        return -1;
    }

    unsigned char response[2];
    if (read(fd, response, 2) != 2) {
        reconnect();
        perror("Error reading");
        return -1;
    }

    return response[0] + 256 * response[1];
}


MaestroControl::~MaestroControl() {
    close(fd);
}


void servoControl(const char *dev, unsigned char servo1_channel, unsigned char servo2_channel, double delay1,
                  int steps1,
                  double delay2, int steps2) {

    signal(SIGINT, signalHandler);
    // 1000000 microseconds = 1 second
    int delay1_us = delay1 * 1000000; // delay between each step for servo 1 in microseconds
    int delay2_us = delay2 * 1000000; // delay between each step for servo 2 in microseconds
    int delta_steps1 = 4000 / steps1; // change per step (servo1)
    int delta_steps2 = 4000 / steps2; // change per step (servo2)
    // Create a new MaestroControl object
    MaestroControl control(dev);
    // Set the servo to the starting position
    std::cout << "Initializing servos" << std::endl;
    sleep(1);
    control.setPosition(servo1_channel, 4000);
    control.setPosition(servo2_channel, 4000);
    sleep(1);
    // Loop through the steps
    std::cout << "Starting servo control" << std::endl;
    for (int i = 1; i <= steps2; i += 2) {
        if (exits) {
            break;
        }
        for (int j = 1; j <= steps1; j++) {
            if (exits) {
                break;
            }
            pos_j = j * delta_steps1 + 4000;
            control.setPosition(servo1_channel, pos_j);
            usleep(delay1_us);
        }
        usleep(delay2_us);
        pos_i = i * delta_steps2 + 4000;
        control.setPosition(servo2_channel, pos_i);
        usleep(delay2_us);
        for (int k = steps1; k >= 0; k--) {
            if (exits) {
                break;
            }
            pos_j = k * delta_steps1 + 4000; // changed pos_k to pos_j
            control.setPosition(servo1_channel, pos_j);
            usleep(delay1_us);
        }
        usleep(delay2_us);
        pos_i = (i + 1) * delta_steps2 + 4000;
        control.setPosition(servo2_channel, pos_i);
        usleep(delay2_us);
    }
    for (int j = 1; j <= steps1; j++) {
        if (exits) {
            break;
        }
        pos_j = j * delta_steps1 + 4000;
        control.setPosition(servo1_channel, pos_j);
        usleep(delay1_us);
    }

    endProcess();
}


void servoShift(const char *dev, unsigned char servo1_channel, unsigned char servo2_channel, double delay1,
                int steps1,
                double delay2, int steps2, int range1, int range2) {
    signal(SIGINT, signalHandler);
    // 1000000 microseconds = 1 second
    int delay1_us = delay1 * 1000000; // delay between each step for servo 1 in microseconds
    int delay2_us = delay2 * 1000000; // delay between each step for servo 2 in microseconds
    int delta_steps1 = range1 / steps1; // change per step (servo1)
    int delta_steps2 = range2 / steps2; // change per step (servo2)
    // Create a new MaestroControl object
    MaestroControl control(dev);
    // Set the servo to the starting position
    cout << endl;
    cout << "********************************************************************************" << endl;
    std::cout << "Initializing servos to center position\nPress any key to start";
    getchar();
    sleep(1);
    cout << endl;
    control.setPosition(servo1_channel, 6000);
    control.setPosition(servo2_channel, 6000);
    cout << endl;
    cout << "********************************************************************************" << endl;
    std::cout << "Initialization complete\nPress any key to start micro shifting";
    getchar();
    sleep(1);
    // Loop through the steps
    cout << endl;
    cout << "********************************************************************************" << endl;
    std::cout << "Starting micro shift" << std::endl;
    // Loop through the steps
    int count = 0;
    while (true) {
        if (exits) {
            break;
        }
        cout << "Iteration " << count << endl;
        for (int i = 6000; i < 6000 + range2; i += delta_steps2) {
            if (exits) {
                break;
            }
            for (int j = 6000; j < 6000 + range1; j += delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000 + range1; j >= 6000; j -= delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000; j > 6000 - range1; j -= delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000 - range1; j <= 6000; j += delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            usleep(delay2_us);
            pos_i = i;
            control.setPosition(servo2_channel, pos_i);
            usleep(delay2_us);
        }

        for (int i = 6000 + range2; i > 6000; i -= delta_steps2) {
            if (exits) {
                break;
            }
            for (int j = 6000; j < 6000 + range1; j += delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000 + range1; j >= 6000; j -= delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000; j > 6000 - range1; j -= delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000 - range1; j <= 6000; j += delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            usleep(delay2_us);
            pos_i = i;
            control.setPosition(servo2_channel, pos_i);
            usleep(delay2_us);
        }

        for (int i = 6000; i > 6000 - range2; i -= delta_steps2) {
            if (exits) {
                break;
            }
            for (int j = 6000; j < 6000 + range1; j += delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000 + range1; j >= 6000; j -= delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000; j > 6000 - range1; j -= delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000 - range1; j <= 6000; j += delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            usleep(delay2_us);
            pos_i = i;
            control.setPosition(servo2_channel, pos_i);
            usleep(delay2_us);
        }

        for (int i = 6000 - range2; i < 6000; i += delta_steps2) {
            if (exits) {
                break;
            }
            for (int j = 6000; j < 6000 + range1; j += delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000 + range1; j >= 6000; j -= delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000; j > 6000 - range1; j -= delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            for (int j = 6000 - range1; j <= 6000; j += delta_steps1) {
                if (exits) {
                    break;
                }
                pos_j = j;
                control.setPosition(servo1_channel, pos_j);
                usleep(delay1_us);
            }
            usleep(delay2_us);
            pos_i = i;
            control.setPosition(servo2_channel, pos_i);
            usleep(delay2_us);
        }
        count++;
    }
    // endProcess();


}

void signalHandler(int signum) {
    force_exit = true;
    exits = true;
    std::cout << std::endl;
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    std::cout << "Current Servo Position: " << std::endl;
    std::cout << "Position of Servo 1:" << pos_j << std::endl;
    std::cout << "Position of Servo 2:" << pos_i << std::endl;
    std::cout << "Press any key to exit...";
    if (OS_WIN) {
        system("pause");
    } else {
        system("read -n 1");
    }

}


void endProcess() {
    if (!force_exit) {
        std::cout << "Process Ended" << std::endl;
        sleep(20);
    } else {
        sleep(20);
    }
}


void print(const string &s) {
    cout << s << endl;
}

