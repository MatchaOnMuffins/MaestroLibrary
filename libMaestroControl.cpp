#include "libMaestroControl.h"
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

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

