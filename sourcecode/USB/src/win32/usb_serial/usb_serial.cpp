#include "usb_serial.hpp"
#include "../../errors/errors.hpp"
using namespace usb;

USB_SERIAL_CONFIG::USB_SERIAL_CONFIG() {
    comPORT = "COM0";

    baudrate = CBR_115200;
    bytesize = 8;
    stopbits = ONESTOPBIT;
    parity = NOPARITY;
    DTRflowControl = DTR_CONTROL_ENABLE;
}

USB_SERIAL_CONFIG::USB_SERIAL_CONFIG(string comPort) {
    comPORT = comPort;

    baudrate = CBR_115200;
    bytesize = 8;
    stopbits = ONESTOPBIT;
    parity = NOPARITY;
    DTRflowControl = DTR_CONTROL_DISABLE; // DTR_CONTROL_ENABLE
}

USB_SERIAL_CONFIG::~USB_SERIAL_CONFIG() {}

//========================================================================

USB_SERIAL_CONN::USB_SERIAL_CONN() {
    serialconfig = USB_SERIAL_CONFIG();
    COMporthandle = HANDLE();
    SerialBusCtrl = DCB();
}

USB_SERIAL_CONN::~USB_SERIAL_CONN() { CloseHandle(COMporthandle); }

int16_t USB_SERIAL_CONN::connect(USB_SERIAL_CONFIG &configuration) {
    serialconfig = configuration;

    COMporthandle =
        CreateFileA(static_cast<LPCSTR>(serialconfig.comPORT.c_str()),
                    GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL, NULL);

    uint32_t ConnectionError = GetLastError();

    if (ConnectionError != 0) {
        return ConnectionError;
    }

    if (!(GetCommState(COMporthandle, &SerialBusCtrl))) {
        throw usbSerialError(1, "Could not get CommState");
    }

    SerialBusCtrl.BaudRate = serialconfig.baudrate;
    SerialBusCtrl.ByteSize = serialconfig.bytesize;
    SerialBusCtrl.StopBits = serialconfig.stopbits;
    SerialBusCtrl.Parity = serialconfig.parity;
    SerialBusCtrl.fDtrControl = serialconfig.DTRflowControl;

    if (!(SetCommState(COMporthandle, &SerialBusCtrl))) {
        throw usbSerialError(2, "Could not set CommState");
    }

    PurgeComm(COMporthandle, PURGE_RXCLEAR | PURGE_TXCLEAR);

    return 0;
}

inline char USB_SERIAL_CONN::read() const {
    static char tempchar = 0;
    static DWORD noOfBytesRead = 0;
    if (ReadFile(COMporthandle, &tempchar, 1, &noOfBytesRead, 0)) {
        return tempchar;
    }
    return -1;
}

void USB_SERIAL_CONN::write(string data) const {
    DWORD noOfBytesWritten = 0;
    WriteFile(COMporthandle, data.c_str(), data.length(), &noOfBytesWritten, 0);
}
