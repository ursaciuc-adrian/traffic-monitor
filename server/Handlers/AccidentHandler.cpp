#include <iostream>
#include <dirent.h>
#include <cstring>

#include "AccidentHandler.h"

AccidentHandler::AccidentHandler(Server *server)
        : Handler(server)
{
}

bool AccidentHandler::canHandle(const Command *com)
{
    m_response = Response();

    if(com->value == "accident")
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

void AccidentHandler::handle(Client *client)
{
    m_server->writeToAllClients("Accident reported on " + m_command->getArgument(0)->getValue() + ".", client->getSocket());
    m_response = Response("Accident reported.", Success);
}

std::string AccidentHandler::getHelpText()
{
    return "accident <location> - reports an accident and notifies all other drivers";
}



