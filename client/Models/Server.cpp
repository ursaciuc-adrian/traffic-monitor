#include "Server.h"

#include <netinet/in.h>
#include <arpa/inet.h>

Server::Server(std::string ip, int port)
{
    /* umplem structura folosita pentru realizarea conexiunii cu serverul */
    /* familia socket-ului */
    server.sin_family = AF_INET;
    /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    /* portul de conectare */
    server.sin_port = htons(static_cast<uint16_t>(port));
}
