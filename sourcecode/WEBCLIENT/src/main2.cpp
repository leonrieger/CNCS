#include <webclient.hpp>

using namespace web;

#include <iostream>
using namespace std;

int main() {

    CLIENT webclient(IP_ADDR(LOCALHOST, 8000));

    HTTP_REQUEST request;
    request.addStatusLine(HTTP_METHOD_POST, "/", HTTP1_1);
    request.addHeader("test1", "sucess");
    request.addBody(HTTP_CONTENT_TEXT_PLAIN, "disvkljvjhfdujfhsjkhjk\nsduufihuichsuijdc\nsduhfjhksd\njdsfhifsdjikc\ndsjhfjkck");

    webclient.write(request.build());
    cout << webclient.read() << endl;

    return 0;
}
