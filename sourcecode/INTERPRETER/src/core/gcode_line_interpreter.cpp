#include "core_interpreter.hpp"

void CNCS::interpreter::gcode_line_interpreter(
    current_interpreter_status& currentstate, std::string line_content,
    pugi::xml_node& root_gcode_node) {
    //------------------------------
    if (line_content[0] == ';') {
        return;
    }
}
