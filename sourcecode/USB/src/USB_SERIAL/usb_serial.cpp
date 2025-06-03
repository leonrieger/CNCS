#include "usb_serial.hpp"
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
    DTRflowControl = DTR_CONTROL_ENABLE;
}

USB_SERIAL_CONFIG::~USB_SERIAL_CONFIG() {}

//========================================================================

USB_SERIAL::USB_SERIAL() {
    serialconfig = USB_SERIAL_CONFIG();
    COMporthandle = HANDLE();
    SerialBusCtrl = DCB();
}

int16_t USB_SERIAL::connect(USB_SERIAL_CONFIG configuration) {
    serialconfig = configuration;

    COMporthandle = CreateFileA(static_cast<LPCSTR>(configuration.comPORT.c_str()),
                                GENERIC_READ | GENERIC_WRITE,
                                NULL,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);

    uint32_t ConnectionError = GetLastError();
}
