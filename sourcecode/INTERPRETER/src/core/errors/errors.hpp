#pragma once

#include <stdint.h>
#include <string>
#include <exception>

class interpreterError : public std::exception {
public:
    interpreterError(uint16_t EID, std::string errorMessage);
    const char* what() const throw();
private:
    std::string errorMessageFormatted = "";
};
