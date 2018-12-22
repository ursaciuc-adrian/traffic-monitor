#pragma once

#include "../Models/Command.h"
#include "Handler.h"
#include "../Models/Client.h"

class LicensePlateHandler: public Handler
{
public:
    explicit LicensePlateHandler(Server *server);

    bool canHandle(const Command *command) override;
    void handle(Client *client) override;
};