#include <iostream>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace std;

vector<uint8_t> SelectComPort() {
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
    for (int port : SelectComPort()) {
        cout << "COM" << port << endl;
    }
    return 0;
}
