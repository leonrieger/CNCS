#pragma once

#include <regex>

//gcode standart regular expression
#define GCODE_STANDARD_REGEX std::regex(R"(^[A-Z][+-]?\d+(\.\d+)?$)")
// all supported gcode g-commands
#define GCODE_SUPPORTED_G_COMMANDS {0, 1, 2, 3}
// all supported gcode m-commands
#define GCODE_SUPPORTED_M_COMMANDS {1, 2, 3}
