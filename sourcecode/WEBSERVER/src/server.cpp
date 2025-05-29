#include "WEBSERVER.hpp"
using namespace webserver;

//https://de.wikipedia.org/wiki/Liste_der_Portnummern

SERVER::SERVER(IP ip_information) {
    own_ip_address = ip_information;

    socket_information.sin_family = AF_INET;
    socket_information.sin_addr.s_addr = inet_addr(ip_information.getIP().c_str());
    socket_information.sin_port = htons(ip_information.getPORT());

    
}
