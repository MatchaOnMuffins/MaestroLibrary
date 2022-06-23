#include <iostream>
#include "libMaestroControl.h"


using namespace std;

int main() {
    MaestroControl control("/dev/cu.usbmodem001033281");
    cout << control.getPosition(0) << endl;
    cout << control.getSerialPort() << endl;
    for (int i = 0; i < 10; i++) {
        control.setPosition(0, 4000);
        usleep(500000);
        control.setPosition(0, 8000);
        usleep(500000);
    }
    return 0;
}
