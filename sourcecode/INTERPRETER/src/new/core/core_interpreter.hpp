#pragma once

#include <string>

namespace CNCS::interpreter {
    enum currentWorkingPlane {
        DEFAULT = 0,
        XY = 1,
        YZ = 2,
        XZ = 3,
    };

    struct current_interpreter_status {
        bool current_unit_system =
            false; // false for metric / true for imperial
        currentWorkingPlane currentPlane;
        bool measurementMode;    // false absolut, true incremental
        uint64_t prevLineNumber; // the previous line number
    }; // namespace current_interpreter_status

    struct number_of_commands_on_one_line {
        uint16_t no_of_commands = 0;
        uint16_t no_of_commands_executed = 0;
    };

    struct line_interpreter_result {
        double X = 0.0;
        double Y = 0.0;
        double Z = 0.0;

        //float A = 0.0f;
        //float B = 0.0f;
        //float C = 0.0f;

        uint16_t S = 0; // Spindle speed

        currentWorkingPlane plane = DEFAULT;

        std::string comment = "";
    };

    void line_interpreter(current_interpreter_status& currentstate,
                          std::string& line_to_interpret, line_interpreter_result& result);
} // namespace CNCS::interpreter
