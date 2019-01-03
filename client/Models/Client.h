#pragma once

#include <string>
#include "Server.h"
#include "../../Shared/Models/Street.h"

class Client
{
    int m_socket;
    fd_set m_master;
    std::string m_licensePlate;
    std::vector<Street*> m_streets;
    Street* m_location = nullptr;
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
    void getStreets();

    std::string generateLicensePlate();

    void updateLocation();
};

