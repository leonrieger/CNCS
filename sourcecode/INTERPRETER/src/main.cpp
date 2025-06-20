// for test purposes only
#include "core/core_interpreter_functions/core_interpreter_functions.hpp"
#include "interpreter.hpp"
#include <algorithm>
#include <interpreter/settings.hpp>
#include <iostream>
#include <pugixml.hpp>
using namespace std;
// clang-format off
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
    /*
    CNCS::interpreter::current_interpreter_status state;
    pugi::xml_document doc;
    pugi::xml_node test = doc.append_child("tesst");

    CNCS::interpreter::gcode_line_parser(state, ";test1234dfuhj s ", test);
    CNCS::interpreter::gcode_line_parser(state, ";sdfkasjd", test);

    doc.save(cout);
    */
    cout << CNCS::interpreter::internal_functions::isValidCommand("G00") << endl;
    cout << CNCS::interpreter::internal_functions::isValidCommand("G1") << endl;
    cout << CNCS::interpreter::internal_functions::isValidCommand("M01") << endl;
    cout << CNCS::interpreter::internal_functions::isValidCommand("M2") << endl;
    cout << CNCS::interpreter::internal_functions::isValidCommand("S10000") << endl;
    cout << CNCS::interpreter::internal_functions::isValidCommand("G57") << endl;
    cout << CNCS::interpreter::internal_functions::isValidCommand("G0000003") << endl;
    cout << CNCS::interpreter::internal_functions::isValidCommand("G07") << endl;

    return 0;
}
// clang-format on
