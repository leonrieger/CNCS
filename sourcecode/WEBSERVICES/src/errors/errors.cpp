#include "errors.hpp"

#include <format>

webServerError::webServerError(uint16_t EID, string errorMessage) {
	this->errorMessageFormatted = string("There occured this webserver error: >> " + errorMessage + format(" <<\tFor futher documentation visit: https://github.com/leonrieger/CNCS/blob/main/documentation/errors/webserver-errors/E{0:05d}.md", EID));
}

const char* webServerError::what() const throw() {
	return errorMessageFormatted.c_str();
}

webClientError::webClientError(uint16_t EID, string errorMessage) {
    this->errorMessageFormatted = string("There occured this webclient error: >> " + errorMessage + format(" <<\tFor futher documentation visit: https://github.com/leonrieger/CNCS/blob/main/documentation/errors/webclient-errors/E{0:05d}.md", EID));
}

const char* webClientError::what() const throw() {
    return errorMessageFormatted.c_str();
}

httpError::httpError(uint16_t EID, string errorMessage) {
    this->errorMessageFormatted = string("There occured this webserver error: >> " + errorMessage + format(" <<\tFor futher documentation visit: https://github.com/leonrieger/CNCS/blob/main/documentation/errors/http-errors/E{0:05d}.md", EID));
}

const char* httpError::what() const throw() {
    return errorMessageFormatted.c_str();
}
