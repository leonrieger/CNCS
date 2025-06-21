#include "ui_elements.hpp"
#include <iostream>

std::string CNCS::cmd::ui_elements::input() {
    std::string input_value = {};
    std::getline(std::cin, input_value);
    return input_value;
}

std::string CNCS::cmd::ui_elements::input(std::string message) {
    std::cout << message;
    std::string input_value = {};
    std::getline(std::cin, input_value);
    return input_value;
}
