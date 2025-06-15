#pragma once

#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace CNCS {
    namespace serial {
        std::vector<uint8_t> getAvailableComPorts();

        class SERIAL_CONFIG {
        public:
            SERIAL_CONFIG();
            SERIAL_CONFIG(std::string comPort);
            SERIAL_CONFIG();

            friend class SERIAL_CONNECTION;

        private:
            uint32_t baudrate;
            std::string comPORT;
            uint8_t bytesize;
            uint8_t stopbits;
            uint8_t parity;
            uint32_t DTRflowControl;
        };

        class SERIAL_CONNECTION {
        public:
            SERIAL_CONNECTION();
            ~SERIAL_CONNECTION();

            int16_t connect(SERIAL_CONFIG &configuration);

            inline char read() const;
            void write(std::string data) const;

        private:
            HANDLE COMporthandle;
            DCB SerialBusCtrl;
        };
    }
}
