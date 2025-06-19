// for test purposes only
#include "interpreter.hpp"
#include <interpreter/settings.hpp>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    /*
    fstream file("test.txt");
    cout << CNCS::filesys::getNumberOfLines(file) << std::endl;
    file.close();*/
    static CNCS::settings::interpreter::USER_ENVIRONMENT_SETTINGS setting_test;
    CNCS::settings::interpreter::load_settings(setting_test);
    cout << setting_test.allow_lowercase_characters_in_comments
         << setting_test.force_line_numbers_declared_with_N
         << setting_test.force_percent_symbol_as_file_begin_and_end
         << std::endl;

    return 0;
}
