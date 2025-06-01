#include "WEBCLIENT.hpp"

using namespace web;

#include <ws2tcpip.h>
#include <memory>

CLIENT::CLIENT(IP_ADDR ip_information) {
    server_ip_info = ip_information;

    server_socket_information.sin_family = AF_INET;
    server_socket_information.sin_port = htons(ip_information.getPORT());
    inet_pton(AF_INET, ip_information.getIP().c_str(), &server_socket_information.sin_addr);

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        WSACleanup();
        throw webClientError(1, "failed to initialise wsa");
    }

    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        WSACleanup();
        throw webClientError(2, "failed to create socket");
    }

    // Connect to the server
    if (connect(server_socket, (sockaddr*)&server_socket_information, sizeof(server_socket_information)) == SOCKET_ERROR) {
        closesocket(server_socket);
        WSACleanup();
        throw webClientError(3, "failed to connect to server");
    }
}

CLIENT::~CLIENT() {
    closesocket(server_socket);
    WSACleanup();
}

void CLIENT::write(string data) {
    int32_t bytesSent;
    int32_t totalBytesSent = 0;
    while (totalBytesSent < data.size()) {
        bytesSent = send(server_socket, data.c_str(), data.size(), 0);
        if (bytesSent < 0) {
            break;
        }
        totalBytesSent += bytesSent;
    }
    if (totalBytesSent != data.size()) {
        throw webClientError(4, "Send failed");
    }
}

string CLIENT::read() {
    const size_t BUFFER_SIZE = 30000;
    vector<char> buffer;
    unique_ptr<char[]> temp(new char[BUFFER_SIZE]);
    int32_t received;

    const string END_OF_HEADERS = "\r\n\r\n";

    while (true) {
        received = recv(server_socket, temp.get(), BUFFER_SIZE, 0);
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
