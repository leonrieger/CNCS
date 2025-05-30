#include "WEBSERVER.hpp"
#include "definitions.hpp"
#include "errors/errors.hpp"

//for multithreading
#include <mutex>
#include <thread>

#include <cstring>
#include <ws2tcpip.h>
#include <format>

using namespace webserver;
using namespace std;

SERVER::SERVER(IP_ADDR ip_information) {
    server_ip_info = ip_information;
    //Throw error if not valid IP-Address
    if (!(server_ip_info.isIPv4()) && !(server_ip_info.isIPv6())) {
        throw webServerError(4, "Invalid IP-Address");
    }

    //Create Socket informations
    if (server_ip_info.isIPv4()) {
        socket_information.sin_family = AF_INET;
    }
    else if (server_ip_info.isIPv6()) {
        socket_information.sin_family = AF_INET6;
    }
    inet_pton(AF_INET, ip_information.getIP().c_str(), &socket_information.sin_addr);
    socket_information.sin_port = htons(server_ip_info.getPORT());

    //Try to ccreate Socket
    try {
        if (server_ip_info.isIPv4()) {
            server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        }
        else {
            server_socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        }
        
    }
    catch (...) {
        throw webServerError(2, "couldn't connect to socket");
    }

    //Generate the size of the server_socket (for speed reasons)
    server_socket_size = sizeof(server_socket);

    //Start Server
    if (WSAStartup(MAKEWORD(2, 2), &server_wsadata) != 0) {
        throw webServerError(1, "");
    }
    //Bind Server to port
    if (bind(server_socket, (sockaddr*)&socket_information, server_socket_size) == SOCKET_ERROR) {
        throw webServerError(3, format("There occured this Binding-Error: {0}", WSAGetLastError()));
    }
}

SERVER::~SERVER() {
    closesocket(server_socket);
    
}

void SERVER::start() {
    webServer = thread(runtime_server);
}

void SERVER::runtime_server() {
    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        throw webServerError(4, "cannot listen to Port!");
    }

    SOCKET client_socket;

    while (!runtime_server_request_to_stop) {
        client_socket = accept(server_socket, (sockaddr*)&socket_information, &server_socket_size);
        //erase buffer on heap
        memset(&buffer, 0, DATA_BUFFER_SIZE);



        while (!runtime_server_allow_continue);
    }

    if (runtime_server_request_to_stop) {
        return;
    }
}

uint16_t SERVER::readAvailable() {
    return abs(bytesReceived);
}
