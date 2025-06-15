#include "serial.hpp"

std::vector<uint8_t> CNCS::serial::getAvailableComPorts() {
    // checks 255 COM-Ports if they have connections --- returns a vector with
    // numbers - for example 3 means "COM3"
    char lpTargetPath[500];
    std::vector<uint8_t> available_ports;

    for (int i = 0; i < 255; i++) {
        std::string str = "COM" + std::to_string(i);
        DWORD test = QueryDosDeviceA(str.c_str(), lpTargetPath, 500);

        if (test != 0) {
            available_ports.push_back(i);
        }
    }
    return available_ports;
}

CNCS::serial::SERIAL_CONFIG::SERIAL_CONFIG() {
    comPORT = "COM0";

    baudrate = CBR_115200;
    bytesize = 8;
    stopbits = ONESTOPBIT;
    parity = NOPARITY;
    DTRflowControl = DTR_CONTROL_ENABLE;
}

CNCS::serial::SERIAL_CONFIG::SERIAL_CONFIG(std::string comPort) {
    comPORT = comPort;

    baudrate = CBR_115200;
    bytesize = 8;
    stopbits = ONESTOPBIT;
    parity = NOPARITY;
    DTRflowControl = DTR_CONTROL_DISABLE; // DTR_CONTROL_ENABLE
}

CNCS::serial::SERIAL_CONFIG::~SERIAL_CONFIG() {}

//========================================================================

CNCS::serial::SERIAL_CONNECTION::SERIAL_CONNECTION() {
    COMporthandle = HANDLE();
    alreadyConnected = true;
}

CNCS::serial::SERIAL_CONNECTION::~SERIAL_CONNECTION() { CloseHandle(COMporthandle); }

int16_t CNCS::serial::SERIAL_CONNECTION::connect(CNCS::serial::SERIAL_CONFIG &configuration) {
    if (alreadyConnected) {
        CloseHandle(COMporthandle);
        alreadyConnected = false;
    }

    COMporthandle =
        CreateFileA(static_cast<LPCSTR>(configuration.comPORT.c_str()),
                    GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL, NULL);

    uint32_t ConnectionError = GetLastError();

    if (ConnectionError != 0) {
        return ConnectionError;
    }

    DCB SerialBusCtrl;

    if (!(GetCommState(COMporthandle, &SerialBusCtrl))) {
        throw CNCS::errors::serialError(1, "Could not get CommState");
    }

    SerialBusCtrl.BaudRate = configuration.baudrate;
    SerialBusCtrl.ByteSize = configuration.bytesize;
    SerialBusCtrl.StopBits = configuration.stopbits;
    SerialBusCtrl.Parity = configuration.parity;
    SerialBusCtrl.fDtrControl = configuration.DTRflowControl;

    if (!(SetCommState(COMporthandle, &SerialBusCtrl))) {
        throw CNCS::errors::serialError(2, "Could not set CommState");
    }

    PurgeComm(COMporthandle, PURGE_RXCLEAR | PURGE_TXCLEAR);

    alreadyConnected = true;

    return 0;
}

inline char CNCS::serial::SERIAL_CONNECTION::read() const {
    char tempchar = 0;
    static DWORD noOfBytesRead = 0;
    if (ReadFile(COMporthandle, &tempchar, 1, &noOfBytesRead, 0)) {
        return tempchar;
    }
    return -1;
}

void CNCS::serial::SERIAL_CONNECTION::write(std::string data) const {
    DWORD noOfBytesWritten = 0;
    WriteFile(COMporthandle, data.c_str(), data.length(), &noOfBytesWritten, 0);
}
