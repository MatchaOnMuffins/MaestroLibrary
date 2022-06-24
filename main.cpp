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
int range1 = 0;
int range2 = 0;

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

    cout << "Please enter the number of steps for servo 2 to move (default is 72 steps): ";
    string input_step2;
    getline(cin, input_step2);
    if (!input_step2.empty()) {
        istringstream stream(input_step2);
        stream >> steps2;
    }
    while (!(range1 <= 2000 && range1 >= 100)) {
        range1 = 1000;
        cout << "Please enter the moving range for servo 1 (must be between 100 and 2000, default is 1000): ";
        string input_range1;
        getline(cin, input_range1);
        if (!input_range1.empty()) {
            istringstream stream(input_range1);
            stream >> range1;
        }
    }
    while (!(range2 <= 2000 && range2 >= 100)) {
        range2 = 1000;
        cout << "Please enter the moving range for servo 2 (must be between 100 and 2000, default is 1000): ";
        string input_range2;
        getline(cin, input_range2);
        if (!input_range2.empty()) {
            istringstream stream(input_range2);
            stream >> range2;
        }
    }
    cout << "The current serial port is: " << serialPort << endl;
    cout << "The current channel number for servo 1 is: " << channel1 << endl;
    cout << "The current channel number for servo 2 is: " << channel2 << endl;
    cout << "The current delay between each move for servo 1 is: " << delay1 << endl;
    cout << "The current delay between each move for servo 2 is: " << delay2 << endl;
    cout << "The current number of steps for servo 1 to move is: " << steps1 << endl;
    cout << "The current number of steps for servo 2 to move is: " << steps2 << endl;
    cout << "The current moving range for servo 1 is: " << range1 << endl;
    cout << "The current moving range for servo 2 is: " << range2 << endl;
    cout << "Press enter to continue..." << std::endl;
    if (OS_WIN) {
        system("pause");
    } else {
        system("read -n 1");
    }
}

int main() {
    /*
     * Prompts the user for method of movement and then calls the appropriate function
     */
    cout << "Welcome to MaestroControl!" << endl;
    cout << "1. Servo Control" << endl;
    cout << "2. Servo Micro Shift" << endl;
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
        if (OS_WIN) {
            system("pause");
        } else {
            system("read -n 1");
        }
        exit(0);
    }
    return 0;
}


