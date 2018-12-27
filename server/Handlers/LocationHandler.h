#pragma once

#include "../Models/Command.h"
#include "Handler.h"
#include "../Models/Client.h"

class LocationHandler: public Handler
{
public:
    explicit LocationHandler(Server *server);

    bool canHandle(const Command *command) override;
    void handle(Client *client) override;
};