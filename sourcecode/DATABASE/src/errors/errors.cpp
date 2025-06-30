#include "errors.hpp"

#include <format>

CNCS::errors::dbError::dbError(uint16_t EID, std::string errorMessage) {
    this->errorMessageFormatted = std::string(
        std::format("Database error: E{0:05d} || ", EID) + errorMessage);
}

const char* CNCS::errors::dbError::what() const throw() {
    return errorMessageFormatted.c_str();
}
