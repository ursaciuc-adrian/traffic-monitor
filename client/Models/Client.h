#pragma once

#include <string>
#include "Server.h"

class Client
{
    int m_socket;
    fd_set m_master;
    std::string m_licensePlate;
    int m_speed;

public:
    explicit Client(int socket, std::string licensePlate);
    void connectToServer(Server *server);

    void select(fd_set &masterCopy);
    void close();
    void write(std::string);

    int getSocket() const;

    void updateSpeed(int speed = -1);
    void updateLicensePlate();

    std::string generateLicensePlate();

    void updateLocation();
};

