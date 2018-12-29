#pragma once

#include "../Models/Command.h"
#include "Handler.h"
#include "../Models/Client.h"

class HelpHandler: public Handler
{
private:
    const std::vector<Handler*> m_handlers;

public:
    explicit HelpHandler(Server *server, std::vector<Handler*> handlers);

    bool canHandle(const Command *command) override;
    void handle(Client *client) override;
    std::string getHelpText() override;
};