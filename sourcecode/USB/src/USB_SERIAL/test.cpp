#include <iostream>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace std;

#include "usb_serial.hpp"

vector<uint8_t> availAbleComPorts() {
    // checks 255 COM-Ports if they have connections --- returns a vector with
    // numbers - for example 3 means "COM3"
    char lpTargetPath[500];
    vector<uint8_t> available_ports;

    for (int i = 0; i < 255; i++) {
        string str = "COM" + to_string(i);
        DWORD test = QueryDosDeviceA(str.c_str(), lpTargetPath, 500);

        if (test != 0) {
            available_ports.push_back(i);
        }
    }
    return available_ports;
}

int main() {
    
    return 0;
}
