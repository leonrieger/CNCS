//for test purposes only
#include "interpreter.hpp"
#include <iostream>
#include <interpreter/settings.hpp>
using namespace std;

int main(int argc, char* argv[]) {
    /*
    if (argc <= 1) {
        std::cout << "not enogh arguments given!" << std::endl;
        return 1;
    }
    *//*
    fstream file("test.txt");
    cout << CNCS::filesys::getNumberOfLines(file) << std::endl;
    file.close();*/
    CNCS::settings::interpreter::USER_ENVIRONMENT_SETTINGS setting_test;
    CNCS::settings::interpreter::load_settings(setting_test);
    cout << setting_test.allow_lowercase_characters_in_comments << std::endl;
    cout << CNCS::settings::interpreter::test() << std::endl;
    return 0;
}
