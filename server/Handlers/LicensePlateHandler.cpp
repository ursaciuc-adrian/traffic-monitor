#include <iostream>
#include <dirent.h>
#include <cstring>

#include "LicensePlateHandler.h"
#include "../Helpers/JsonHelper.h"

LicensePlateHandler::LicensePlateHandler(Server *server)
        : Handler(server)
{
}

bool LicensePlateHandler::canHandle(const Command *com)
{
    m_response = Response();

    if(com->value == "update_licensePlate")
    {
        if(com->getArgument(0) != nullptr)
        {
            m_command = com;
            return true;
        }
        else
        {
            m_response = Response("No license plate provided.", Error);
        }
    }

    return false;
}

void LicensePlateHandler::handle(Client *client)
{
    std::string licensePlate = this->m_command->getArgument(0)->getValue();
    client->setLicensePlate(licensePlate);

    if(!JsonHelper::getClient(licensePlate, client))
    {
        JsonHelper::addClient(client);
    }

    m_response = Response("License plate was set to " + licensePlate + ".", Success);
}



