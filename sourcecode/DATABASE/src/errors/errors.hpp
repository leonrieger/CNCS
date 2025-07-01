#pragma once

#include <exception>
#include <string>

namespace CNCS::errors {
    class dbError : public std::exception {
    public:
        dbError(uint16_t EID, std::string errorMessage);
        const char* what() const throw();

    private:
        std::string errorMessageFormatted;
    };
} // namespace CNCS::errors
