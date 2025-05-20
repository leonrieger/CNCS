#include "errors.hpp"

databaseError::databaseError(uint16_t EID, string errorMessage) {
	this->errorMessageFormatted = string("There occured this database error: >> " + errorMessage + " <<\tFor futher documentation visit: https://github.com/leonrieger/CNCS/blob/main/documentation/errors/database-errors/E%5d.md", EID);
}

const char* databaseError::what() const throw() {
	return errorMessageFormatted.c_str();
}
