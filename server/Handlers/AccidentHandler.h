#pragma once

#include "../Models/Command.h"
#include "Handler.h"
#include "../Models/Client.h"

class AccidentHandler: public Handler
{
public:
    explicit AccidentHandler(Server *server);

    bool canHandle(const Command *command) override;
    void handle(Client *client) override;
};