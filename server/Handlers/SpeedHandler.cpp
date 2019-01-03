#include <iostream>
#include <dirent.h>
#include <cstring>

#include "SpeedHandler.h"
#include "../../Shared/Models/Street.h"
#include "../Helpers/JsonHelper.h"

SpeedHandler::SpeedHandler(Server *server)
    : Handler(server)
{
}

bool SpeedHandler::canHandle(const Command *com)
{
    m_response = Response();

    if(com->value == "speed")
    {
        if(com->getArgument(0) != nullptr)
        {
            m_command = com;
            return true;
        }
        else
        {
            m_response = Response("No speed provided.", Error);
        }
    }

    return false;
}

void SpeedHandler::handle(Client *client)
{
    std::string speed = this->m_command->getArgument(0)->getValue();
    client->setSpeed(std::stoi(speed));

    if(client->getSpeed() <= client->getLocation()->speedLimit / 2)
    {
        m_server->writeToAllClients(client->getLicensePlate() + " reported heavy traffic on \"" + client->getLocation()->name + "\".", client->getSocket());
    }

    m_response = Response("Speed was updated to " + speed + ".", Success);
}

std::string SpeedHandler::getHelpText()
{
    return "speed <your_speed> - updates your speed";
}



