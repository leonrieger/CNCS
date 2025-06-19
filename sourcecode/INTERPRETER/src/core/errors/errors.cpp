#include "errors.hpp"

#include <format>

interpreterError::interpreterError(uint16_t EID, std::string errorMessage) {
    this->errorMessageFormatted = std::string(std::format("Fatal Interpreter Error: E{0:05d} || ", EID) + errorMessage);
}

const char* interpreterError::what() const throw() {
    return errorMessageFormatted.c_str();
}
