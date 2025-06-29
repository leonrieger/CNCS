#pragma once

#include "webstandartfunctions.hpp"

#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

namespace web {
    class CLIENT {
    public:
        CLIENT(IP_ADDR ip_information);
        ~CLIENT();

        string read();
        void write(string data);

    private:
        IP_ADDR server_ip_info;

        sockaddr_in server_socket_information;
        SOCKET server_socket;
        int32_t bytesReceived = 0;
    };
} // namespace web
