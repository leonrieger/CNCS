#pragma once

#include <string>
#include <exception>

namespace CNCS {
    namespace errors {
        class serialError : public std::exception {
        public:
            serialError(uint16_t EID, std::string errorMessage);
            const char* what() const throw();

        private:
            std::string errorMessageFormatted;
        };
    }
}