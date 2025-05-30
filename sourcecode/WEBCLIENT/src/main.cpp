#include <winsock2.h>
#include <iostream>
#include <string>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed." << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up the server address (example.com, port 80)
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);  // HTTP port
    //server.sin_addr.s_addr = inet_addr("127.0.0.1");  // IP address of example.com
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Connection failed." << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Send HTTP GET request
    std::string request = "GET / HTTP/1.1\r\n";
    request += "Host: example.com\r\n";
    request += "Connection: close\r\n";
    request += "\r\n";  // End of headers

    int bytesSent = send(sock, request.c_str(), request.length(), 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Send failed." << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Receive the response
    char buffer[1024];
    int bytesReceived;
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';  // Null-terminate the buffer
        std::cout << buffer;
    }

    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "Recv failed." << std::endl;
    }

    // Close the socket
    closesocket(sock);

    // Clean up Winsock
    WSACleanup();

    return 0;
}