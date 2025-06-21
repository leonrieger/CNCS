#pragma once

#include <pugixml.hpp>
#include <string>
#include <vector>
#include <interpreter/settings.hpp>

namespace CNCS::interpreter {
    enum currentWorkingPlane {
        NONE = 0,
        XY = 1,
        YZ = 2,
        XZ = 3,
    };

    struct INTERPRETER_STATUS {
        bool current_unit_system =
            false; // false for metric / true for imperial
        bool programstartsymbol_exists_already = false;
        bool programstopsymbol_exists_already = false;
        currentWorkingPlane currentPlane = NONE;
        bool measurementMode = false; // false absolute, true incremental
        uint64_t prevLineNumber = 0;  // the previous line number
        uint64_t prevCommandID = 0;
    };

    //void gcode_file_parser(std::string absolute_path_to_file);

    int8_t
    gcode_line_parser(INTERPRETER_STATUS& currentstate,
                      CNCS::settings::interpreter::USER_ENVIRONMENT_SETTINGS
                          user_env_settings,
                      std::string line_content,
                      pugi::xml_node& root_gcode_node);
} // namespace CNCS::interpreter

// unparse