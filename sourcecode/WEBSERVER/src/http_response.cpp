#include "WEBSERVER.hpp"
#include "definitions.hpp"
#include "errors/errors.hpp"

using namespace webserver;

HTTP_RESPONSE::HTTP_RESPONSE() {}

HTTP_RESPONSE::~HTTP_RESPONSE() {}

void HTTP_RESPONSE::addStatusLine(string http_version, uint16_t status_code, string reason) {
    status_line = http_version + " " + to_string(status_code) + " " + reason + "\r\n";
}

void HTTP_RESPONSE::addHeader(string name, string content) {
    headers.push_back(name + ": " + content + "\r\n");
}

void HTTP_RESPONSE::addBody(string data) {
    body = data + "\r\n";
}

string HTTP_RESPONSE::build() {
    string temp = status_line;
    return "";
}

//https://www.tutorialspoint.com/http/http_responses.htm
//https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Messages