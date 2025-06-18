//for test purposes only
#include "interpreter.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    /*
    if (argc <= 1) {
        std::cout << "not enogh arguments given!" << std::endl;
        return 1;
    }
    */
    fstream file("test.txt");
    cout << CNCS::filesys::getNumberOfLines(file) << std::endl;
    file.close();

    return 0;
}
