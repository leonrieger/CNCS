#include "WEBSERVER.hpp"
#include "errors/errors.hpp"

#include <ws2tcpip.h>
#ifdef _DEBUG
#include <iostream>
#include <sstream>
#endif

//https://de.wikipedia.org/wiki/Liste_der_Portnummern

webserver::SERVER::SERVER(webserver::IP_ADDR ip_information) {
    own_ip_address = ip_information;

    socket_information.sin_family = AF_INET;
    inet_pton(AF_INET, ip_information.getIP().c_str(), &socket_information.sin_addr);
    socket_information.sin_port = htons(ip_information.getPORT());

    if (WSAStartup(MAKEWORD(2, 2), &server_wsadata) != 0) {
        throw webServerError(1, "");
    }

    try{
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
    } catch (...) {
        WSACleanup();
        throw webServerError(2, "couldn't connect to socket");
    }
    /*
    if (bind(server_socket, (sockaddr*)&socket_information, sizeof(socket_information) == SOCKET_ERROR)) {
        WSACleanup();
        throw webServerError(3, string(WSAGetLastError()));
    }
    */
    server_socket_size = sizeof(socket_information);
    if (bind(server_socket, (sockaddr*)&socket_information, server_socket_size) == SOCKET_ERROR) {
        WSACleanup();
        ostringstream oss;
        oss << WSAGetLastError(); // Convert the error code to a string
        throw webServerError(3, oss.str());
    }
}

webserver::SERVER::~SERVER() {
    closesocket(server_socket);
    WSACleanup();
}

void webserver::SERVER::run() {
    if (listen(server_socket, SOMAXCONN) < 0)
    {
        throw webServerError(4, "cannot listen to Port!");
    }
    #ifdef _DEBUG
    char ipstr[INET_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET, &(socket_information.sin_addr), ipstr, INET_ADDRSTRLEN);
    cout << "\n*** Listening on ADDRESS: " << ipstr << " PORT: " << ntohs(socket_information.sin_port) << " ***\n\n";
    #endif
    const uint16_t BUFFER_SIZE = 65525;
    int32_t bytesReceived = 0;

    bool requestToStop = false;

    while (!requestToStop) {
        cout << "-----Waiting for new Connection-----" << endl;

        client_socket = accept(server_socket, (sockaddr*)&socket_information, &server_socket_size);
        if (client_socket == SOCKET_ERROR) {
            cout << "error connecting to client socket" << endl;
            while (true);
        }
        char buffer[BUFFER_SIZE] = { 0 };



    }

}
