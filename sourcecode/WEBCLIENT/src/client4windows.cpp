#include "WEBCLIENT.hpp"

using namespace web;

#include <ws2tcpip.h>

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

}

string CLIENT::read() {

}

void CLIENT::end() {

}
