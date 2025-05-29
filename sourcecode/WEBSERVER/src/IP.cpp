#include "WEBSERVER.hpp"
#include "definitions.hpp"

using namespace webserver;

IP_ADDR::IP_ADDR() {
    IP_address = LOCALHOST;
    internal_port = 8080;
}

IP_ADDR::IP_ADDR(string address, uint16_t port) {
    IP_address = address;
    internal_port = port;
}

string IP_ADDR::getIP() {
    return IP_address;
}

uint16_t IP_ADDR::getPORT() {
    return internal_port;
}
