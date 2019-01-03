#include <iostream>
#include <dirent.h>
#include <cstring>

#include "LocationHandler.h"
#include "../Helpers/JsonHelper.h"

LocationHandler::LocationHandler(Server *server)
        : Handler(server)
{
}

bool LocationHandler::canHandle(const Command *com)
{
    m_response = Response();

    if(com->value == "location")
    {
        if(com->getArgument(0) != nullptr)
        {
            m_command = com;
            return true;
        }
        else
        {
            m_response = Response("No location provided.", Error);
        }
    }

    return false;
}

void LocationHandler::handle(Client *client)
{
    int location = std::stoi(this->m_command->getArgument(0)->getValue());
    client->setLocation(Street::getStreet(location));

    m_response = Response("Location was updated to \"" + client->getLocation()->name + "\" (" + std::to_string(client->getLocation()->speedLimit) + ").", Success);
}

std::string LocationHandler::getHelpText()
{
    return "location <location> - updates your location";
}



