#include "version_selector.hpp"
/*
#include <iostream>

int main() {
    CNCS::toolkit::TOOLKIT tk;
    tk.set(CNCS::settings::CURRENT_VERSION);

    CNCS::toolkit::TOOLKIT_INTERFACE tki;
    std::cout << tki.load(tk) << std::endl;

    std::unordered_map<std::string, void*> temp = {
        {"test", nullptr}
    };

    tki.get_functions(temp);

    std::cout << temp.at("test") << std::endl;

    typedef void (*test_fkt)(const char*);
    test_fkt tfk = static_cast<test_fkt>(temp.at("test"));

    if (tfk == nullptr) {
        std::cout << "ne";
    } else {
        tfk("hello world");
    }

    return 0;
}
*/