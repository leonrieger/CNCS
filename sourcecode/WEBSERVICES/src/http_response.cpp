#include "webstandartfunctions.hpp"
#include "definitions.hpp"
#include "errors/errors.hpp"

using namespace web;

HTTP_RESPONSE::HTTP_RESPONSE() {
    status_line = "";
    body = "";
}

HTTP_RESPONSE::~HTTP_RESPONSE() {}

void HTTP_RESPONSE::addStatusLine(string http_version, uint16_t status_code, string reason) {
    status_line = http_version + " " + to_string(status_code) + " " + reason + "\r\n";
}

void HTTP_RESPONSE::addHeader(string name, string content) {
    headers.push_back(name + ": " + content + "\r\n");
}

void HTTP_RESPONSE::addBody(string type, string data) {
    addHeader("Content-Type", type);
    addHeader("Content-Length", to_string(data.size()));

    body = data + "\r\n";
}

string HTTP_RESPONSE::build() {
    string temp = status_line;
    if (!(headers.empty())) {
        for (string header : headers) {
            temp += header;
        }
        temp += "\r\n";
    }
    if (body != "") {
        temp += body;
    }
    return temp;
}
