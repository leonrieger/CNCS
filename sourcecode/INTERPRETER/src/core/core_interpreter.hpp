#pragma once

#include <pugixml.hpp>
#include <string>
#include <vector>

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

    void gcode_line_parser(current_interpreter_status& currentstate,
                           std::string line_content,
                           pugi::xml_node& root_gcode_node);
} // namespace CNCS::interpreter

// unparse