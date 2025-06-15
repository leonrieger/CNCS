#include "serial.hpp"

#include <iostream>

int main() {
    CNCS::serial::SERIAL_CONFIG config("COM3");
    CNCS::serial::SERIAL_CONNECTION conn;

    conn.connect(config);

    while (1) {
        conn.write("Test sucess\n");
        std::cout << conn.readStringUntil('\n', 2000);
    }
}
