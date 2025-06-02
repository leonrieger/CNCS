#pragma once

#include <stdint.h>
#include <string>
using namespace std;

namespace usb {
    class USB_SERIAL {
    public:
        USB_SERIAL();
        ~USB_SERIAL();

        uint16_t available();
        inline char read();
        void write(string text);

        string readStringUntil(char endCharacter);
    private:
    };

    class USB_SERIAL_CONFIG {
    public:
        USB_SERIAL_CONFIG(string comPort, uint32_t baudrate);
        ~USB_SERIAL_CONFIG();
    private:
    };
}
