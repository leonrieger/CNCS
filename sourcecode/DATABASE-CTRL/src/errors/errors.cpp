#include "errors.hpp"

databaseError::databaseError(uint16_t EID, string errorMessage) {
	errorID = EID;
	errorMsg = errorMessage;
}

const char* databaseError::what() const throw() {
	//format the output a bit
	errorMessageFormatted = "There occured this database error: >> "+errorMsg+" <<\tFor futher documentation visit: https://github.com/leonrieger/CNCS/blob/main/documentation/errors/database-errors/E%5d.md",errorID;

	return errorMessageFormatted.c_str();
}
