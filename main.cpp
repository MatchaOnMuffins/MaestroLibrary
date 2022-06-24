#include <iostream>
#include "lib/libMaestroControl.h"
#include <sstream>
#include <string>

using namespace std;

std::string serialPort;
int channel1;
int channel2;
double delay1 = 0.1;
double delay2 = 0.5;
int steps1 = 360;
int steps2 = 72;

void prompts() {
    cout
            << "Please enter the serial port of your Maestro (this can be found by running 'ls /dev/cu.usbmodem* ' in the terminal): ";
    cin >> serialPort;
    cout << "Please enter the channel number for servo 1: ";
    cin >> channel1;
    cout << "Please enter the channel number for servo 2: ";
    cin >> channel2;
    getchar();
    cout << "Please enter the delay between each move for servo 1 in seconds: (default is 0.1 seconds)";


    string input1;
    getline(cin, input1);
    if (!input1.empty()) {
        istringstream stream(input1);
        stream >> delay1;
    }
    cout << "delay1" << delay1;

    cout << "Please enter the delay between each move for servo 2 in seconds: (default is 0.5 seconds)";


    string input2;
    getline(cin, input2);
    if (!input2.empty()) {
        istringstream stream(input2);
        stream >> delay2;
    }

    cout << "Please enter the number of steps for servo 1 to move: (default is 360 steps)";


    string input_step1;
    getline(cin, input_step1);
    if (!input_step1.empty()) {
        istringstream stream(input_step1);
        stream >> steps1;
    }

    cout << "Please enter the number of steps for servo 2 to move: (default is 72 steps)";


    string input_step2;
    getline(cin, input_step2);
    if (!input_step2.empty()) {
        istringstream stream(input_step2);
        stream >> steps2;
    }
    cout << "The current serial port is: " << serialPort << endl;
    cout << "The current channel number for servo 1 is: " << channel1 << endl;
    cout << "The current channel number for servo 2 is: " << channel2 << endl;
    cout << "The current delay between each move for servo 1 is: " << delay1 << endl;
    cout << "The current delay between each move for servo 2 is: " << delay2 << endl;
    cout << "The current number of steps for servo 1 to move is: " << steps1 << endl;
    cout << "The current number of steps for servo 2 to move is: " << steps2 << endl;
    cout << "Press enter to continue..." << std::endl;
    getchar();
}

void shiftPrompt() {
    cout
            << "Please enter the serial port of your Maestro (this can be found by running 'ls /dev/cu.usbmodem* ' in the terminal): ";
    cin >> serialPort;
    cout << "Please enter the channel number for servo 1: ";
    cin >> channel1;
    cout << "Please enter the channel number for servo 2: ";
    cin >> channel2;
    getchar();
    cout << "Please enter the delay between each move for servo 1 in seconds: (default is 0.1 seconds)";


    string input1;
    getline(cin, input1);
    if (!input1.empty()) {
        istringstream stream(input1);
        stream >> delay1;
    }
    cout << "delay1" << delay1;

    cout << "Please enter the delay between each move for servo 2 in seconds: (default is 0.5 seconds)";


    string input2;
    getline(cin, input2);
    if (!input2.empty()) {
        istringstream stream(input2);
        stream >> delay2;
    }

    cout << "Please enter the number of steps for servo 1 to move: (default is 360 steps)";


    string input_step1;
    getline(cin, input_step1);
    if (!input_step1.empty()) {
        istringstream stream(input_step1);
        stream >> steps1;
    }

    cout << "Please enter the number of steps for servo 2 to move: (default is 72 steps)";


    string input_step2;
    getline(cin, input_step2);
    if (!input_step2.empty()) {
        istringstream stream(input_step2);
        stream >> steps2;
    }
    cout << "The current serial port is: " << serialPort << endl;
    cout << "The current channel number for servo 1 is: " << channel1 << endl;
    cout << "The current channel number for servo 2 is: " << channel2 << endl;
    cout << "The current delay between each move for servo 1 is: " << delay1 << endl;
    cout << "The current delay between each move for servo 2 is: " << delay2 << endl;
    cout << "The current number of steps for servo 1 to move is: " << steps1 << endl;
    cout << "The current number of steps for servo 2 to move is: " << steps2 << endl;
    cout << "Press enter to continue..." << std::endl;
    getchar();
}

int main() {
    cout << "Welcome to MaestroControl!" << endl;
    cout << "1. Servo Control" << endl;
    cout << "2. Servo Shift" << endl;
    cout << "Which method would you like to use? (1 or 2): ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        prompts();
        servoControl(serialPort.c_str(), channel1, channel2, delay1, steps1, delay2, steps2);
    } else if (choice == 2) {
        shiftPrompt();
        servoShift(serialPort.c_str(), channel1, channel2, delay1, steps1, delay2, steps2);
    } else {
        cout << "Invalid choice" << endl;
        cout << "Press enter to exit..." << endl;
        getchar();
        exit(0);
    }
    return 0;
}


