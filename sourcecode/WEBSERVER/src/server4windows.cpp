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
        throw webServerError(2, "couldn't connect to socket");
    }
#ifdef _DEBUG
    char ipstr[INET_ADDRSTRLEN] = { 0 };
    inet_ntop(AF_INET, &(socket_information.sin_addr), ipstr, INET_ADDRSTRLEN);
    cout << "\n*** Listening on ADDRESS: " << ipstr << " PORT: " << ntohs(socket_information.sin_port) << " ***\n\n";
#endif
}

SERVER::~SERVER() {
    closesocket(server_socket);
}

void SERVER::startup() {
    if (bind(server_socket, (sockaddr*)&socket_information, server_socket_size) == SOCKET_ERROR) {
        int32_t lastError = WSAGetLastError();
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
    try {
        cerr << "called suspicios problem" << endl;
        //memset(&buffer, 0x0, BUFFER_SIZE);//this is the bastard
        const uint16_t BUFFER_SIZE = 30000;
        char buffer[BUFFER_SIZE] = {};
        cerr << "we got far" << endl;
        bytesReceived = recv(client_socket, buffer, BUFFER_SIZE, 0);
        cerr << "we got farer" << endl;
        if (bytesReceived < 0) {
            throw webServerError(6, "Number of received bytes smaller than one");
        }
#ifdef _DEBUG
        cout << "***received request from client***" << endl;
        cout << string(buffer) << endl << "**********************" << endl;
#endif
        return string(buffer);
    }
    catch (...) {
        cerr << "here it is:)" << endl;
        return "aaaa";
    }
}

void SERVER::write(string data) {
    int32_t bytesSent;
    int32_t totalBytesSent = 0;
    while (totalBytesSent < data.size()) {
        bytesSent = send(client_socket, data.c_str(), data.size(), 0);
        if (bytesSent < 0) {
            break;
        }
        totalBytesSent += bytesSent;
    }
    if (totalBytesSent != data.size()) {
#ifdef _DEBUG
        cout << "send failed" << endl;
#endif
        throw webServerError(7, "Send failed");
    }
}

void SERVER::cycleFinish() {
    closesocket(client_socket);
}
