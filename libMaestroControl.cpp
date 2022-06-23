#include "libMaestroControl.h"
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>

#ifdef _WIN32
#define O_NOCTTY 0
//#include <Windows.h>
#else

#endif


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
    for (int i = 0; i < (steps2 / 2); i += 2) {
        for (int j = 0; j < steps1; j++) {
            int pos_j = j * delta_steps1 + 4000;
            control.setPosition(servo1_channel, pos_j);
            usleep(delay1_us);
        }
        int pos_i_first = i * delta_steps2 + 4000;
        control.setPosition(servo2_channel, pos_i_first);
        usleep(delay2_us);
        for (int k = steps1; k > 0; k--) {
            int pos_k = k * delta_steps1 + 4000;
            control.setPosition(servo1_channel, pos_k);
            usleep(delay1_us);
        }
        usleep(delay2_us);
        int pos_i_second = (i + 1) * delta_steps2 + 4000;
        control.setPosition(servo2_channel, pos_i_second);
    }
}
