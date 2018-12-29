#pragma once

#include "../Models/Command.h"
#include "Handler.h"
#include "../Models/Client.h"

class SpeedHandler: public Handler
{
public:
    explicit SpeedHandler(Server *server);

    bool canHandle(const Command *command) override;
    void handle(Client *client) override;
    std::string getHelpText() override;
};