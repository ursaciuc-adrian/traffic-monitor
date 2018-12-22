#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

class Client
{
    int m_socket;
    int m_port;
    int m_speed;
    std::string m_ip;
    std::string m_licensePlate;
    std::vector<std::string> m_subscriptions;

public:
    Client(int socket, std::string ip, int port);
    int getSocket();

    void setSpeed(int speed);
    void setLicensePlate(std::string licensePlate);
    void addSubscription(std::string subscription);

    ~Client();

    std::string getLicensePlate();
};