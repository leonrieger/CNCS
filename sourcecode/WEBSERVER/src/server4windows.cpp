#include "WEBSERVER.hpp"
#include "definitions.hpp"
#include "errors/errors.hpp"

using namespace webserver;

#include <ws2tcpip.h>

webserver::SERVER::SERVER(webserver::IP_ADDR ip_information) {
    server_ip_info = ip_information;

    //client_socket = socket(AF_INET, SOCK_STREAM, 0);

    socket_information.sin_family = AF_INET;
    inet_pton(AF_INET, ip_information.getIP().c_str(), &socket_information.sin_addr);
    socket_information.sin_port = htons(ip_information.getPORT());

    if (WSAStartup(MAKEWORD(2, 2), &server_wsadata) != 0) {
        throw webServerError(1, "");
    }

    try {
        server_socket = socket(AF_INET, SOCK_STREAM, 0);//AF_INET=IPv4 || AF_INET6=IPv6
    }
    catch (...) {
        WSACleanup();
        throw webServerError(2, "couldn't connect to socket");
    }

    server_socket_size = sizeof(socket_information);
    if (bind(server_socket, (sockaddr*)&socket_information, server_socket_size) == SOCKET_ERROR) {
        ostringstream oss;
        oss << WSAGetLastError(); // Convert the error code to a string
        WSACleanup();
        throw webServerError(3, oss.str());
    }
}

webserver::SERVER::~SERVER() {
    closesocket(server_socket);

    WSACleanup();
}

