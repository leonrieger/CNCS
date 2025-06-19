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
    };

    void gcode_file_parser();

    bool gcode_line_parser(current_interpreter_status& currentstate,
                           std::string line_content,
                           pugi::xml_node& root_gcode_node);
} // namespace CNCS::interpreter

// unparse