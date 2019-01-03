#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include "../../Shared/Models/Street.h"

class Client
{
    int m_socket;
    int m_speed;
    Street* m_location;
    std::string m_licensePlate;
    std::vector<std::string> m_subscriptions;

public:
    Client(int socket);
    int getSocket();

    void setSpeed(int speed);
    void setLocation(Street* location);
    void setLicensePlate(std::string licensePlate);
    void addSubscription(std::string subscription);
    bool hasSubscription(std::string subscription);
    std::vector<std::string> getSubscriptions();
    ~Client();

    std::string getLicensePlate();

    Street* getLocation();

    int getSpeed();
};