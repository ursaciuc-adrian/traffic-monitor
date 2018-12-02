#include "Server.h"

#include <netinet/in.h>
#include <arpa/inet.h>

Server::Server(std::string ip, int port)
    : m_ip(ip), m_port(port)
{
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_port = htons(static_cast<uint16_t>(port));
}
