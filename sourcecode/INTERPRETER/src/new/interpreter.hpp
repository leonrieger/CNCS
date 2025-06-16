#pragma once

#include <string>

namespace CNCS {
    namespace interpreter {
        enum currentWorkingPlane {
            XY = 1,
            YZ = 2,
            XZ = 3,
        };

        union current_interpreter_status {
            bool current_unit_system;//false for metric / true for imperial
            int8_t currentplane;// baseed on 'currentWorkingPlane'
        };

        struct interpreter_configuration {};

        struct interpreter_result {

            double X = 0;
            double Y = 0;
            double Z = 0;

            double A = 0;
            double B = 0;
            double C = 0;
        };

        interpreter_result line_interpreter(current_interpreter_status& status, std::string& line);
    }
}
