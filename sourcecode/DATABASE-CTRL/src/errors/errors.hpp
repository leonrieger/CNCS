#pragma once

#include <stdint.h>
#include <string>

#include <exception>
using namespace std;

class databaseError :public exception {
public:
	databaseError(uint16_t EID, string errorMessage);

	const char* what() const throw();

private:
	string errorMessageFormatted = "";
};
//https://github.com/leonrieger/CNCS/blob/main/documentation/errors/gcode-errors/e-0001.md