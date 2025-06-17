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
        bool current_unit_system; // false for metric / true for imperial
        //int8_t currentplane;      // based on 'currentWorkingPlane'
        currentWorkingPlane currentPlane;
        bool measurementMode;     // false absolut, true incremental
        uint64_t prevLineNumber;  // the previous line number
    }; // namespace current_interpreter_status

    struct interpreter_configuration {};

    struct interpreter_result {
        double X = 0.0;
        double Y = 0.0;
        double Z = 0.0;

        float A = 0.0f;
        float B = 0.0f;
        float C = 0.0f;
    };

    interpreter_result line_interpreter(current_interpreter_status& currentstate, std::string& line);
} // namespace CNCS::interpreter
