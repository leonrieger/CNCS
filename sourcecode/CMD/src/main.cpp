#include <iostream>
#include <string>

#include "ui_elements/ui_elements.hpp"

using namespace std;
using namespace ui_elements;
/*
#include <iostream>
using namespace std;
int main() {
    int width = 0, height = 0;
    get_terminal_size(width, height);
    cout << "width=" << width << ", height=" << height << endl;
    for (int i=0; i < width; i++) {
        cout << "=";
    }
    //cin.get();
    return 0;
}
*/
//int main( int argc, char* argv[] ) {
    /*
    if (argc >= 2) {
        cout << "Testapplication" << "\t#of Args: " << argc << endl;
        for (int i = 0; i < argc; i++) {
            cout << "State: " << i << " || " << argv[i] << endl;
        }
    }
    else if (argc <= 1) {
        char input[1000] = {};
        cout << "sucess" << endl << ">>> ";

        cin >> input;
    }
    */

//}

int main() {
    color_table colors;
    cout << colors.FAIL;
    cout << "Input-test" << endl;
    cout << common::input() << endl;
    cout << "#2" << endl;
    cout << common::input("new Input") << endl;
    cout << colors.ENDC;
}
