#include "WEBSERVER.hpp"
#include "definitions.hpp"
#include "errors/errors.hpp"

using namespace webserver;

#include <ws2tcpip.h>
#include <format>

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
}

SERVER::~SERVER() {
    closesocket(server_socket);
}

void SERVER::startup() const {
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

string SERVER::read() const {
    const size_t BUFFER_SIZE = 30000;
    vector<char> buffer;
    unique_ptr<char[]> temp(new char[BUFFER_SIZE]);
    int32_t received;

    const string END_OF_HEADERS = "\r\n\r\n";

    while (true) {
        received = recv(client_socket, temp.get(), BUFFER_SIZE, 0);
        if (received < 0) {
            throw webServerError(6, "Number of received bytes smaller than one");
        }
        if (received == 0) {
            break;
        }
        buffer.insert(buffer.end(), temp.get(), temp.get() + received);

        if (buffer.size() >= END_OF_HEADERS.size()) {
            std::string buf_str(buffer.data(), buffer.size());
            if (buf_str.find(END_OF_HEADERS) != std::string::npos) {
                break;
            }
        }
        if (received < BUFFER_SIZE) {
            break;
        }
    }
    return string(buffer.data(), buffer.size());
}

void SERVER::write(string data) const {
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
        throw webServerError(7, "Send failed");
    }
}

void SERVER::cycleFinish() const {
    closesocket(client_socket);
}
