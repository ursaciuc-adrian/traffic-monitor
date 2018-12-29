#include <iostream>
#include <dirent.h>
#include <cstring>

#include "HelpHandler.h"
#include "../Helpers/JsonHelper.h"

HelpHandler::HelpHandler(Server *server, const std::vector<Handler*> handlers)
        : Handler(server, true, true), m_handlers(handlers)
{
}

bool HelpHandler::canHandle(const Command *com)
{
    m_response = Response();

    if(com->value == "help")
    {
        m_command = com;
        return true;
    }

    return false;
}

void HelpHandler::handle(Client *client)
{
    std::string help;
    help += "Here is a list with all commands:\n";

    for (auto const &handler: this->m_handlers)
    {
        help += handler->getHelpText() + "\n";
    }
    help += this->getHelpText();

    m_response = Response(help, Success);
}

std::string HelpHandler::getHelpText()
{
    return "help - get a list of all commands";
}



