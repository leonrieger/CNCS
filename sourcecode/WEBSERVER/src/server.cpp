#include "WEBSERVER.hpp"
using namespace webserver;

//https://de.wikipedia.org/wiki/Liste_der_Portnummern

SERVER::SERVER(IP ip_information) {
    own_ip_address = ip_information;
    socket_information.sin_family = AF_INET;
    string test = ip_information.getIP();
    socket_information.sin_addr.s_addr = inet_addr(test.c_str());

}
