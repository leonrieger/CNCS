#pragma once

#include "../core_interpreter.hpp"

namespace CNCS::interpreter::internal_functions {
    void extractComments(std::string& command, std::vector<std::string>& comments);
    void splitbyWhitespace(std::string input_string, std::vector<std::string>& output_vector);
    bool isValidFormatting(std::string string_to_be_validated);
    bool isValidCommand(std::string& gcode_command);
}
