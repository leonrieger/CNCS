#include "WEBGENERAL.hpp"
#include "definitions.hpp"
#include "errors/errors.hpp"

using namespace web;

HTTP_REQUEST::HTTP_REQUEST() {
    status_line = "";
    body = "";
}

HTTP_REQUEST::~HTTP_REQUEST() {}

void HTTP_REQUEST::addStatusLine(string method, string path, string http_version) {
    status_line = method + " " + path + " " + http_version + "\r\n";
}

void HTTP_REQUEST::addHeader(string name, string content) {
    headers.push_back(name + ": " + content + "\r\n");
}

void HTTP_REQUEST::addBody(string type, string data) {
    addHeader("Content-Type", type);
    addHeader("Content-Length", to_string(data.size()));

    body = data + "\r\n";
}

string HTTP_REQUEST::build() {
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
