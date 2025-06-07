#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

bool SelectComPort() //added function to find the present serial 
{
    char lpTargetPath[5000]; // buffer to store the path of the COMPORTS
    bool gotPort = false; // in case the port is not found

    for (int i = 0; i < 255; i++) {
        std::string str = "COM" + std::to_string(i);
        DWORD test = QueryDosDeviceA(str.c_str(), lpTargetPath, 5000);

        if (test != 0) {
            std::cout << str << ": " << lpTargetPath << std::endl;
            gotPort = true;
        }
    }

    return gotPort;
}

int main() {
    SelectComPort();
    return 0;
}
