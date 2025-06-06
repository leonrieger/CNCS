#include <webserver.hpp>
#include <definitions.hpp>

#include <iostream>
#include <sstream>
using namespace std;

using namespace web;

int main() {
    try {
        SERVER testserver1(IP_ADDR("10.118.192.4", 8000));
        testserver1.startup();
        while (true) {
            try {
                testserver1.waitForHttpRequest();
                cout << testserver1.read().c_str() << endl;
                string htmlFile = "<!DOCTYPE html><html><head><title>sucess</title></head><body><h1> HOME </h1><p> Hello World </p></body></html>";
                HTTP_RESPONSE response;
                response.addStatusLine(HTTP1_1, HTTP_STATUS_OK, HTTP_REASON_OK);
                response.addBody(HTTP_CONTENT_TEXT_HTML, htmlFile);
                testserver1.write(response.build());
                testserver1.cycleFinish();
            }
            catch (...) {
                cerr << "inner error" << endl;
            }
        }
    }
    catch (...) {
        cerr << "outer error" << endl;
    }
    WSACleanup();
    return 0;
}

/*
int main() {
    HTTP_RESPONSE response;

    response.addStatusLine(HTTP1_1, HTTP_STATUS_OK, HTTP_REASON_OK);
    response.addHeader("Header-Test", "test_sucess");
    response.addBody(HTTP_CONTENT_TEXT_PLAIN, "djflskdöadlsjdvhffvjldkss\njoskidvhjoscljcol\nsihjdfisoasdvughfisjdodkufjrofl\nifdkxksjcdojkdjckdjckdjck");
    cout << response.build() << endl;
}
*/
/*
string htmlFile = "<!DOCTYPE html><html><head><title>absolute sucess</title></head><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
ostringstream ss;
ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n" << htmlFile;
*/