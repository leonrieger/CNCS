#pragma once

#include <stdint.h>
#include <string>
#include <exception>

using namespace std;

class webServerError : public exception {
public:
    webServerError(uint16_t EID, string errorMessage);
    const char* what() const throw();
private:
    string errorMessageFormatted = "";
};

class webClientError : public exception {
public:
    webClientError(uint16_t EID, string errorMessage);
    const char* what() const throw();
private:
    string errorMessageFormatted = "";
};

class httpError : public exception {
public:
    httpError(uint16_t EID, string errorMessage);
    const char* what() const throw();
private:
    string errorMessageFormatted = "";
};
