#pragma once

#include <regex>

//gcode standart regular expression
#define GCODE_STANDART_REGEX std::regex(R"(^[+-]?\d+(\.\d+)?$)")
