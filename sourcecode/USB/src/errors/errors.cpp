#include "errors.hpp"

#include <format>

usbSerialError::usbSerialError(uint16_t EID, string errorMessage) {
	this->errorMessageFormatted = string(format("USB Serial Error: E{0:05d} || ", EID) + errorMessage);
}

const char* usbSerialError::what() const throw() {
	return errorMessageFormatted.c_str();
}
//this->errorMessageFormatted = string("There occured this webserver error: >> " + errorMessage + format(" <<\tFor futher documentation visit: https://github.com/leonrieger/CNCS/blob/main/documentation/errors/webserver-errors/E{0:05d}.md", EID));
