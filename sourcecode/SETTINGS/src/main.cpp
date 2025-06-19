#include "OS.hpp"
#include <iostream>
using namespace std;

int main() {
    cout << CNCS::settings::os::getCurrentUserName() << std::endl;
    return 0;
}
