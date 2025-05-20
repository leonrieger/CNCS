#pragma once

#ifdef DLLEXPORT
#	define DLLMODE __declspec(dllexport)
#else
#	define DLLMODE __declspec(dllimport)
#endif

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
