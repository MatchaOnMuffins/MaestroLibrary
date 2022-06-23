#include <iostream>
#include "libMaestroControl.h"
#include <sstream>
#include <string>

using namespace std;

void signalHandler(int signum);

string serialPort;
int channel1;
int channel2;

int main() {
    signal(SIGINT, signalHandler);
    cout << "Welcome to MaestroControl!" << endl;
    cout << "Please enter the serial port of your Maestro: ";
    cin >> serialPort;
    cout << "Please enter the channel number for servo 1: ";
    cin >> channel1;
    cout << "Please enter the channel number for servo 2: ";
    cin >> channel2;
    getchar();
    cout << "Please enter the delay between each move for servo 1 in seconds: (default is 0.1 seconds)";
    double delay1 = 0.1;
    std::string input1;
    std::getline(std::cin, input1);
    if (!input1.empty()) {
        std::istringstream stream(input1);
        stream >> delay1;
    }
    cout << "Please enter the delay between each move for servo 2 in seconds: (default is 0.5 seconds)";
    double delay2 = 0.5;
    std::string input2;
    std::getline(std::cin, input2);
    if (!input2.empty()) {
        std::istringstream stream(input2);
        stream >> delay2;
    }
    cout << "Please enter the number of steps for servo 1 to move: (default is 360 steps)";
    int steps1 = 360;
    std::string input_step1;
    std::getline(std::cin, input_step1);
    if (!input2.empty()) {
        std::istringstream stream(input_step1);
        stream >> steps1;
    }
    cout << "Please enter the number of steps for servo 2 to move: (default is 72 steps)";
    int steps2 = 72;
    std::string input_step2;
    std::getline(std::cin, input_step2);
    if (!input2.empty()) {
        std::istringstream stream(input_step2);
        stream >> steps2;
    }
    cout << "The current serial port is: " << serialPort << endl;
    cout << "The current channel number for servo 1 is: " << channel1 << endl;
    cout << "The current channel number for servo 2 is: " << channel2 << endl;
    cout << "The current delay between each move for servo 1 is: " << delay1 << endl;
    cout << "The current delay between each move for servo 2 is: " << delay2 << endl;
    cout << "The current number of steps for servo 1 to move is: " << steps1 << endl;
    cout << "The current number of steps for servo 2 to move is: " << steps2 << endl;
    cout << "Press enter to continue...";
    getchar();
    servoControl(serialPort.c_str(), channel1, channel2, delay1, steps1, delay2, steps2);
    // servoControl("/dev/cu.usbmodem001033281", 0, 5, 0.05, 100, 0.5, 72);
    return 0;
}

void signalHandler(int signum) {
    cout << endl;
    cout << "Interrupt signal (" << signum << ") received.\n";
    cout << "Current Servo Position: " << endl;
    MaestroControl posGetter(serialPort.c_str());
    cout << "Servo 1: " << posGetter.getPosition(channel1) << endl;
    cout << "Servo 2: " << posGetter.getPosition(channel2) << endl;
    cout << "Press any key to exit" << endl;
    getchar();
    cout << "Exiting..." << endl;
    getchar();
    exit(signum);
}