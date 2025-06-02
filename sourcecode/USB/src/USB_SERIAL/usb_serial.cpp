#include "usb_serial.hpp"

using namespace usb;

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

USB_SERIAL::USB_SERIAL(USB_SERIAL_CONFIG configuration) {
    COMporthandle = CreateFileA(static_cast<LPCSTR>(configuration.comPORT.c_str()), 
                                GENERIC_READ | GENERIC_WRITE, 
                                NULL, 
                                NULL, 
                                OPEN_EXISTING, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL);

    uint32_t ConnectionError = GetLastError();
}
