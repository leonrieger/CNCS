#include <iostream>

using namespace std;

int main( int argc, char* argv[] ) {
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
}
