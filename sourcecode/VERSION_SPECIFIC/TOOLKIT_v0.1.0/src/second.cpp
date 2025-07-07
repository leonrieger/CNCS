#include "toolkit.hpp"
#include <iostream>

extern "C" __declspec(dllexport)
void test(const char* name) {
    std::cout << "Hello, test success: " << name << std::endl;
}
