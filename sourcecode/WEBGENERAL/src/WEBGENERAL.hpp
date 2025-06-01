#pragma once

#include "definitions.hpp"
#include "errors/errors.hpp"

#include <vector>

using namespace std;

namespace web {
    class IP_ADDR { //compatible with IPv4 --- IPv6 support missing
    public:
        IP_ADDR();
        //IP(string address);
        IP_ADDR(string address, uint16_t port);
        //IP(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint16_t port);
        //IP(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4, uint16_t block5, uint16_t block6, uint16_t block7, uint16_t block8, uint16_t port);

        bool isIPv4();
        bool isIPv6();

        string getIP();
        uint16_t getPORT();
    private:
        bool type = true; // true if IPv4
        string IP_address;
        uint16_t internal_port; // 1024<port<49151!
    };

    //==============================================================================

    class HTTP_RESPONSE {
    public:
        HTTP_RESPONSE();
        ~HTTP_RESPONSE();

        void addStatusLine(string http_version, uint16_t status_code, string reason);
        void addHeader(string name, string content);
        void addBody(string type, string data);

        string build();
    private:
        string status_line;
        vector<string> headers;
        string body;
    };
}
