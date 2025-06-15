#pragma once

#include <stdint.h>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace usb {
    class USB_SERIAL_CONFIG {
    public:
        USB_SERIAL_CONFIG();
        USB_SERIAL_CONFIG(std::string comPort);
        ~USB_SERIAL_CONFIG();

        friend class USB_SERIAL_CONN;

    private:
        uint32_t baudrate;
        std::string comPORT;
        uint8_t bytesize;
        uint8_t stopbits;
        uint8_t parity;
        uint32_t DTRflowControl;
    };

    class USB_SERIAL_CONN {
    public:
        USB_SERIAL_CONN();
        ~USB_SERIAL_CONN();

        int16_t connect(USB_SERIAL_CONFIG &configuration);

        inline char read() const;
        void write(std::string data) const;

    private:
        USB_SERIAL_CONFIG serialconfig;

        HANDLE COMporthandle;
        DCB SerialBusCtrl;
        // COMSTAT status;
        // DWORD error;
    };
} // namespace usb
