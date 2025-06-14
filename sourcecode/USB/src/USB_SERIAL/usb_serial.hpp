#pragma once

#include <stdint.h>
#include <string>
using namespace std;

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace usb {
    class USB_SERIAL_CONFIG {
    public:
        USB_SERIAL_CONFIG();
        USB_SERIAL_CONFIG(string comPort);
        ~USB_SERIAL_CONFIG();

        friend class USB_SERIAL;
    private:
        uint32_t baudrate;
        string comPORT;
        uint8_t bytesize;
        uint8_t stopbits;
        uint8_t parity;
        uint32_t DTRflowControl;
    };

    class USB_SERIAL {
    public:
        USB_SERIAL();
        ~USB_SERIAL();

        int16_t connect(USB_SERIAL_CONFIG configuration);

        string read();
        void write(string text);

    private:
        USB_SERIAL_CONFIG serialconfig;

        HANDLE COMporthandle;
        DCB SerialBusCtrl;
        //COMSTAT status;
        //DWORD error;
    };
}
