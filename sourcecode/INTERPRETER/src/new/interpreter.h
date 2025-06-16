#pragma once

#include <string>

namespace CNCS {
    namespace interpreter {
        struct interpreter_configuration {};

        struct interpreter_result {
            
            double X = 0;
            double Y = 0;
            double Z = 0;

            double A = 0;
            double B = 0;
            double C = 0;

        };

        interpreter_result line_interpreter(std::string& line);
    } // namespace interpreter
} // namespace CNCS
