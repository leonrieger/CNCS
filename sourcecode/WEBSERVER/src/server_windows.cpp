#include "WEBSERVER.hpp"
#include "definitions.hpp"
#include "errors/errors.hpp"

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

    //Start Server
    if (WSAStartup(MAKEWORD(2, 2), &server_wsadata) != 0) {
        throw webServerError(1, "");
    }
    
    //Try to create Socket
    try {
        if (server_ip_info.isIPv4()) {
            server_socket = socket(AF_INET, SOCK_STREAM, 0);//IPPROTO_TCP
        }
        /*
        else {
            server_socket = socket(AF_INET6, SOCK_STREAM, 0);
        }
        */
    }
    catch (...) {
        throw webServerError(2, "couldn't connect to socket");
    }

    //Generate the size of the server_socket (for speed reasons)
    server_socket_size = sizeof(socket_information); // FIX: use sizeof(socket_information) instead of sizeof(server_socket)

    //Bind Server to port
    if (bind(server_socket, (sockaddr*)&socket_information, server_socket_size) == SOCKET_ERROR) {
        throw webServerError(3, format("There occured this Binding-Error: {0}", WSAGetLastError()));
    }

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        throw webServerError(4, "cannot listen to Port!");
    }
}

SERVER::~SERVER() {
    closesocket(server_socket);
    WSACleanup();
}

void SERVER::start() {
    runtime_server();
}

void SERVER::runtime_server() {
    

    SOCKET client_socket;
        client_socket = accept(server_socket, (sockaddr*)&socket_information, &server_socket_size);
        //erase buffer on heap
        memset(&read_buffer, 0, DATA_BUFFER_SIZE);

        bytesReceived = recv(client_socket, read_buffer, DATA_BUFFER_SIZE, 0);

        while (!runtime_server_allow_continue);
        runtime_server_allow_continue = false;
        bytesReceived = 0;

        int64_t bytesSent;
        int64_t totalBytesSent = 0;

        if (write_message != "") {
            while (totalBytesSent < write_message.size()) {
                bytesSent = send(client_socket, write_message.c_str(), write_message.size(), 0);
                if (bytesSent < 0)
                {
                    break;
                }
                totalBytesSent += bytesSent;
            }
        }
}

uint16_t SERVER::readAvailable() {
    return abs(bytesReceived);
}

string SERVER::read() {
    return string(read_buffer);
}

void SERVER::write(string data) {
    write_message = data;
}

void SERVER::allowContinue() {
    runtime_server_allow_continue = true;
}
