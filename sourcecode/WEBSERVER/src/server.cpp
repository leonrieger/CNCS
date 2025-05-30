#include "WEBSERVER.hpp"
#include "definitions.hpp"
#include "errors/errors.hpp"

#include <thread>
#include <ws2tcpip.h>
//#include <iphlpapi.h> //---iphlpapi.lib; inkludieren bei linker
//#include <Windns.h>

#ifdef _DEBUG
#include <iostream>
#include <sstream>
#endif

webserver::SERVER::SERVER(webserver::IP_ADDR ip_information) {
    server_ip_info = ip_information;

    //client_socket = socket(AF_INET, SOCK_STREAM, 0);

    socket_information.sin_family = AF_INET;
    inet_pton(AF_INET, ip_information.getIP().c_str(), &socket_information.sin_addr);
    socket_information.sin_port = htons(ip_information.getPORT());
    
    if (WSAStartup(MAKEWORD(2, 2), &server_wsadata) != 0) {
        throw webServerError(1, "");
    }
    
    try{
        server_socket = socket(AF_INET, SOCK_STREAM, 0);//AF_INET=IPv4 || AF_INET6=IPv6
    } catch (...) {
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

    const uint16_t BUFFER_SIZE = 40000;
    int32_t bytesReceived = 0;

    bool requestToStop = false;

    while (!requestToStop) {
        cout << "-----Waiting for new Connection-----" << endl;

        client_socket = accept(server_socket, (sockaddr*)&socket_information, &server_socket_size);
        if (client_socket == SOCKET_ERROR) {
            cout << "error connecting to client socket" << endl;
            cin.get();
        }
        //char buffer[BUFFER_SIZE] = { 0 };
        char* buffer = new char [BUFFER_SIZE]{ 0 };//new keyword//allocate on heap

        bytesReceived = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived < 0) {
            cout << "bytesReceived smaller than one" << endl;
            cin.get();
        }
        cout << "***received request from client***" << endl;
        cout << string(buffer) << endl << "**********************" << endl;

        string htmlFile = "<!DOCTYPE html><html><head><title>absolute sucess</title></head><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
        std::ostringstream ss;
        ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n" << htmlFile;
        string message = ss.str();

        int bytesSent;
        long totalBytesSent = 0;

        while (totalBytesSent < message.size())
        {
            bytesSent = send(client_socket, message.c_str(), message.size(), 0);
            if (bytesSent < 0)
            {
                break;
            }
            totalBytesSent += bytesSent;
        }
        
        if (totalBytesSent == message.size())
        {
            cout << "------ Server Response sent to client ------\n\n" << endl;
        }
        else
        {
            cout << "Error sending response to client." << endl;
        }
        delete(&buffer);
        closesocket(client_socket);
    }

}
