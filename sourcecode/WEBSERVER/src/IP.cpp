#include "WEBSERVER.hpp"
#include "definitions.hpp"

using namespace webserver;

IP::IP() {
    IP_address = LOCALHOST;
    internal_port = 8080;
}

IP::IP(string address, uint16_t port) {
    IP_address = address;
    internal_port = port;
}

string IP::getIP() {
    return IP_address;
}

uint16_t IP::getPORT() {
    return internal_port;
}
