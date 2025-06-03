#pragma once

#include <stdint.h>
#include <string>
#include <exception>

using namespace std;

class usbSerialError : public exception {
public:
    usbSerialError(uint16_t EID, string errorMessage);
    const char* what() const throw();
private:
    string errorMessageFormatted = "";
};
