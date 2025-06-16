#pragma once

#include <string>

namespace CNCS {
    namespace interpreter {
        union current_interpreter_status {
            bool current_unit_system; // false for metric / true for imperial
            int8_t currentplane;      // baseed on 'currentWorkingPlane'
            bool measurementMode;     // false absolut, true inkremental
            uint64_t prevLineNumber;  // the previous line number
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

        interpreter_result line_interpreter(current_interpreter_status& status,
                                            std::string& line);
    } // namespace interpreter

    namespace cnc_machine {
        namespace tools {
            struct toolID {
                uint16_t machineID;
                uint8_t toolClass;
                uint8_t toolSubClass;
                uint16_t toolIdentifier;
                uint16_t toolSubIdentifier;
            };

            std::string generateToolIdString(toolID& toolidentifier);
            toolID generateToolIdStruct(std::string& toolidentifier);

        } // namespace tools

        enum currentWorkingPlane {
            DEFAULT = 0,
            XY = 1,
            YZ = 2,
            XZ = 3,
        };

    } // namespace cnc_machine
} // namespace CNCS
