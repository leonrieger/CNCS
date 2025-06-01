#pragma once

#include <WEBGENERAL.hpp>

#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

namespace web {
    class CLIENT {
    public:
        CLIENT(IP_ADDR ip_information);
        ~CLIENT();

        string read();
        void write(string data);
        void end();

    private:
        IP_ADDR server_ip_info;

        sockaddr_in server_socket_information;
        SOCKET server_socket;
        int32_t server_socket_size;
        WSADATA server_wsadata;

        int32_t bytesReceived = 0;
    };
}
