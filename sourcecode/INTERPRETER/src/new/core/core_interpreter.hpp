#pragma once  

#include <string>  
#include <vector>  
#include <pugixml.hpp>  

// Ensure "pch.h" is included only if it exists  
#ifdef __has_include  
#if __has_include("pch.h")  
#include "pch.h"  
#endif  
#endif  

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

    struct interpreted_commands {  
        //units in mm  
        double X = 0.0;  
        double Y = 0.0;  
        double Z = 0.0;  

        uint16_t S = 0; // Spindle speed  

        currentWorkingPlane plane = DEFAULT;  

        std::string comment = "";  
    };  

    void gcode_line_interpreter(current_interpreter_status& currentstate,  
                          std::string& file_content,  
                          std::vector<interpreted_commands>& cnc_program_commands);  
} // namespace CNCS::interpreter
