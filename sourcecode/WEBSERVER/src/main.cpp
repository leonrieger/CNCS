#include "WEBSERVER.hpp"
#include "definitions.hpp"

#include <iostream>
using namespace std;

using namespace webserver;

int main() {
    try {
        SERVER testserver1(IP_ADDR(LOCALHOST, 8000));


    }
    catch (...) {
        cout << "error" << endl;
    }
}
