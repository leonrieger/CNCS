#include "WEBSERVER.hpp"
#include "definitions.hpp"
#include "errors/errors.hpp"

using namespace webserver;

#include <ws2tcpip.h>
#include <format>

#ifdef _DEBUG
#   include <iostream>
#endif

SERVER::SERVER(webserver::IP_ADDR ip_information) {
    server_ip_info = ip_information;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    socket_information.sin_family = AF_INET;
    inet_pton(AF_INET, ip_information.getIP().c_str(), &socket_information.sin_addr);
    socket_information.sin_port = htons(ip_information.getPORT());

    server_socket_size = sizeof(socket_information);
    
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
}

SERVER::~SERVER() {
    closesocket(server_socket);

    WSACleanup();
}

void SERVER::startup() {
    if (bind(server_socket, (sockaddr*)&socket_information, server_socket_size) == SOCKET_ERROR) {
        int32_t lastError = WSAGetLastError();
        WSACleanup();
        throw webServerError(3, format("Error in 'bind': {0} ", lastError));
    }
    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        throw webServerError(4, "cannot listen to Port!");
    }
}

void SERVER::waitForHttpRequest() {
    client_socket = accept(server_socket, (sockaddr*)&socket_information, &server_socket_size);
    if (client_socket == SOCKET_ERROR) {
        throw webServerError(5, "Could not connect to client socket");
    }
}

string SERVER::read() {
    bytesReceived = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytesReceived < 0) {
        throw webServerError(6, "Number of received bytes smaller than one");
    }
#ifdef _DEBUG
    cout << "***received request from client***" << endl;
    cout << string(buffer) << endl << "**********************" << endl;
#endif
    return string(buffer);
}
