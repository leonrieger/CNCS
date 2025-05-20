#include "errors.hpp"

#include <format>

databaseError::databaseError(uint16_t EID, string errorMessage) {
	this->errorMessageFormatted = string("There occured this database error: >> " + errorMessage + format(" <<\tFor futher documentation visit: https://github.com/leonrieger/CNCS/blob/main/documentation/errors/database-errors/E{0:05d}.md", EID));
}

const char* databaseError::what() const throw() {
	return errorMessageFormatted.c_str();
}

void test_throw_error() {
	throw databaseError(1, "I hope this works!");
}
