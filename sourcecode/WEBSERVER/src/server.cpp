#include "WEBSERVER.hpp"
//using namespace webserver;

#include "errors/errors.hpp"

//https://de.wikipedia.org/wiki/Liste_der_Portnummern

webserver::SERVER::SERVER(webserver::IP_ADDR ip_information) {
    own_ip_address = ip_information;

    socket_information.sin_family = AF_INET;
    socket_information.sin_addr.s_addr = inet_addr(ip_information.getIP().c_str());
    socket_information.sin_port = htons(ip_information.getPORT());

    if (WSAStartup(MAKEWORD(2, 2), &server_wsadata) != 0) {
        throw webServerError(1, "");
    }

    try{
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
    } catch (const std::exception& e) {
        WSACleanup();
        throw webServerError(2, "couldn't connect to socket");
    }
}

webserver::SERVER::~SERVER() {
    closesocket(server_socket);
    WSACleanup();
}
