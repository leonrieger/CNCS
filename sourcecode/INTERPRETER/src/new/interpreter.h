#pragma once

#include <string>

namespace CNCS {
    namespace interpreter {
        struct interpreter_configuration {};

        struct interpreter_result {};

        interpreter_result line_interpreter(std::string& info);
    } // namespace interpreter
} // namespace CNCS
