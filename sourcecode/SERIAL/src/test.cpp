#include "serial.hpp"

#include <iostream>

int main() {
    CNCS::serial::SERIAL_CONFIG config("COM3");
    CNCS::serial::SERIAL_CONNECTION conn;

    conn.connect(config);

    while (1) {
        std::cerr << conn.read();
        conn.write("Test sucess\n");
    }
}
