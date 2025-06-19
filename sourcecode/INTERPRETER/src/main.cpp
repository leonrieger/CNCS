// for test purposes only
#include "interpreter.hpp"
#include <interpreter/settings.hpp>
#include <iostream>
#include <pugixml.hpp>
using namespace std;

int main(int argc, char* argv[]) {
    /*
    fstream file("test.txt");
    cout << CNCS::filesys::getNumberOfLines(file) << std::endl;
    file.close();*/
    /*
    static CNCS::settings::interpreter::USER_ENVIRONMENT_SETTINGS setting_test;
    CNCS::settings::interpreter::load_settings(setting_test);
    cout << setting_test.allow_lowercase_characters_in_comments
         << setting_test.force_line_numbers_declared_with_N
         << setting_test.force_percent_symbol_as_file_begin_and_end
         << std::endl;
    */

    CNCS::interpreter::current_interpreter_status state;
    pugi::xml_document doc;
    pugi::xml_node test = doc.append_child("tesst");

    CNCS::interpreter::gcode_line_parser(state, ";test1234dfuhj s ", test);
    CNCS::interpreter::gcode_line_parser(state, ";sdfkasjd", test);
    CNCS::interpreter::gcode_line_parser(state, ";abcdefg", test);
    CNCS::interpreter::gcode_line_parser(state, ";qwertzui", test);
    CNCS::interpreter::gcode_line_parser(state, ";yxcvbnm", test);
    CNCS::interpreter::gcode_line_parser(state, ";asdfghjkl", test);
    CNCS::interpreter::gcode_line_parser(state, ";wsxdfrfvbghzhn", test);
    CNCS::interpreter::gcode_line_parser(state, ";1525646553", test);
    CNCS::interpreter::gcode_line_parser(state, ";f5gfg45f4g5f", test);

    doc.save(cout);

    return 0;
}
