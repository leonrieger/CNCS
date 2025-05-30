#include "WEBSERVER.hpp"
#include "definitions.hpp"

#include <iostream>
#include <sstream>
using namespace std;

using namespace webserver;

int main() {
    
    try {
        SERVER testserver1(IP_ADDR(LOCALHOST, 8000));
        testserver1.start();
        while (true) {
            if (testserver1.readAvailable()) {
                string htmlFile = "<!DOCTYPE html><html><head><title>absolute sucess</title></head><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
                ostringstream ss;
                ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n" << htmlFile;
                string message = ss.str();
                testserver1.write(message);
                testserver1.allowContinue();
            }
        }
    }
    catch (webServerError& err) {
        cout << "error" << err.what() << endl;
    }
    return 0;

}
