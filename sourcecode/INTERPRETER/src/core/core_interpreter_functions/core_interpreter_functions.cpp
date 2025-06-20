#include "core_interpreter_functions.hpp"
#include <interpreter/gcode_specifications.hpp>

#include <sstream>

void CNCS::interpreter::internal_functions::extractComments(
    std::string& command, std::vector<std::string>& comments) {
    size_t startposition, stopposition;

    while ((startposition = command.find('(')) != std::string::npos &&
           (stopposition = command.find(')', startposition)) !=
               std::string::npos) {
        std::string extracted_comment =
            command.substr(startposition + 1, stopposition - startposition - 1);
        comments.push_back(extracted_comment);
        command.erase(startposition, stopposition - startposition + 1);
    }
}

void CNCS::interpreter::internal_functions::splitbyWhitespace(
    std::string input_string, std::vector<std::string>& output_vector) {
    std::istringstream iss(input_string);
    std::string token;

    while (iss >> token) {
        output_vector.push_back(token);
    }
}

bool CNCS::interpreter::internal_functions::isValidFormatting(
    std::string string_to_be_validated) {
    return std::regex_match(string_to_be_validated, GCODE_STANDART_REGEX);
}

bool CNCS::interpreter::internal_functions::isValidCommand(
    std::string gcode_command) {
    char cmd_family = gcode_command[0];
    int16_t cmd_code = static_cast<int16_t>(std::stoi(gcode_command.substr(1)));
    bool isValid = false;

    switch (cmd_family) {
    case 'G':
        for (int16_t validation_value : GCODE_SUPPORTED_G_COMMANDS) {
            if (cmd_code == validation_value) {
                isValid = true;
                break;
            }
        }
        break;
    case 'M':
        for (int16_t validation_value : GCODE_SUPPORTED_M_COMMANDS) {
            if (cmd_code == validation_value) {
                isValid = true;
                break;
            }
        }
        break;
    case 'S':
        isValid = true;
        break;
    }

    return isValid;
}
