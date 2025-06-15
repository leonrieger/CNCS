#include "errors.hpp"

#include <format>

CNCS::errors::serialError::serialError(uint16_t EID, std::string errorMessage) {
    this->errorMessageFormatted = std::string(std::format("USB Serial Error: E{0:05d} || ", EID) + errorMessage);
}

const char* CNCS::errors::serialError::what() const throw() {
    return errorMessageFormatted.c_str();
}
