#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

class Client
{
    int m_socket;
    int m_port;
    int m_speed;
    int m_location;
    std::string m_ip;
    std::string m_licensePlate;
    std::vector<std::string> m_subscriptions;

public:
    Client(int socket, std::string ip, int port);
    int getSocket();

    void setSpeed(int speed);
    void setLocation(int location);
    void setLicensePlate(std::string licensePlate);
    void addSubscription(std::string subscription);
    bool hasSubscription(std::string subscription);
    std::vector<std::string> getSubscriptions();
    ~Client();

    std::string getLicensePlate();

    int getLocation();

    int getSpeed();
};