#pragma once

#include "../Models/Command.h"
#include "Handler.h"
#include "../Models/Client.h"

class SpeedHandler: public Handler
{
public:
    SpeedHandler();

    bool canHandle(const Command *command) override;
    void handle(Client *client);
};