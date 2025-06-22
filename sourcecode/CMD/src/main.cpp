#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

#include "ui_elements/ui_elements.hpp"

int main(int argc, char* argv[]) {
    CLI::App app{"App description"};
    argv = app.ensure_utf8(argv);

    std::string filename = "default";
    app.add_option("-f,--file", filename, "A help string");
    app.add_option("-t,--test", filename,
                   "a general test of the functionality");

    CLI11_PARSE(app, argc, argv);
    return 0;
}
