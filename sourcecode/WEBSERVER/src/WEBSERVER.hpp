#pragma once

#include <WEBGENERAL.hpp>

#include <string>
using namespace std;

#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

namespace web {
    class SERVER {
    public:
        SERVER(IP_ADDR ip_information);
        ~SERVER();

        void startup() const;
        void waitForHttpRequest();
        string read() const;
        void write(string data) const;
        void cycleFinish() const;

    private:
        IP_ADDR server_ip_info;

        sockaddr_in socket_information;
        SOCKET server_socket;
        int32_t server_socket_size;
        SOCKET client_socket;
        WSADATA server_wsadata;

        int32_t bytesReceived = 0;
    };
}
