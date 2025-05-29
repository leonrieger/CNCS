#pragma once

#include "errors/errors.hpp"

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
//#include <Windows.h>

namespace webserver {
    class IP_ADDR { //compatible with IPv4 --- IPv6 support missing
    public:
        IP_ADDR();
        //IP(string address);
        IP_ADDR(string address, uint16_t port);
        //IP(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint16_t port);
        //IP(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4, uint16_t block5, uint16_t block6, uint16_t block7, uint16_t block8, uint16_t port);

        string getIP();
        uint16_t getPORT();
    private:
        string IP_address;
        uint16_t internal_port;//1024<port<49151!
    };

    class SERVER {
    public:
        SERVER(IP_ADDR ip_information);
        ~SERVER();

        //string getIP();
    private:
        IP_ADDR own_ip_address;

        sockaddr_in socket_information;
        SOCKET server_socket;
        WSADATA server_wsadata;
    };
}
//uuid for systems
