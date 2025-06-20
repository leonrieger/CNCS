// for test purposes only
#include "core/core_interpreter_functions/core_interpreter_functions.hpp"
#include "interpreter.hpp"
#include <algorithm>
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
    /*
    CNCS::interpreter::current_interpreter_status state;
    pugi::xml_document doc;
    pugi::xml_node test = doc.append_child("tesst");

    CNCS::interpreter::gcode_line_parser(state, ";test1234dfuhj s ", test);
    CNCS::interpreter::gcode_line_parser(state, ";sdfkasjd", test);

    doc.save(cout);
    */
    /*
    std::vector<std::string> testv;

    CNCS::interpreter::internal_functions::splitbyWhitespace("uewifjk ewiofjewn
    fioewfn wefioewh f ewifhwe fewf e   fw iofn ewf we  fiwef we f weoi",
    testv);

    for (std::string str : testv) {
        std::replace(str.begin(), str.end(), " ", "0");
        cout << str << std::endl;
    }
    */
    // clang-format off
    cout << CNCS::interpreter::internal_functions::isValidFormatting("G10") << endl;
    cout << CNCS::interpreter::internal_functions::isValidFormatting("M-10") << endl;
    cout << CNCS::interpreter::internal_functions::isValidFormatting("X10.0") << endl;
    cout << CNCS::interpreter::internal_functions::isValidFormatting("J10") << endl;
    cout << CNCS::interpreter::internal_functions::isValidFormatting("a10") << endl;
    cout << CNCS::interpreter::internal_functions::isValidFormatting("10") << endl;
    cout << CNCS::interpreter::internal_functions::isValidFormatting("100.001") << endl;
    cout << CNCS::interpreter::internal_functions::isValidFormatting("SS10") << endl;
    // clang-format on
    return 0;
}
