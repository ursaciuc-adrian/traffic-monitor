#pragma once

#include <string>
#include <iterator>
#include <sstream>
#include <iostream>

#include "../Models/Command.h"

static const Command* deserializeInput(std::string inputString)
{
    auto *command = new Command();
    std::string arg;

    std::istringstream iss(inputString);
    std::string token;

    bool firstToken = true;
    inputString += " ";
    for(int i = 0; i < inputString.length(); i++){

        if(inputString[i] == ' ')
        {
            if(firstToken)
            {
                command->value = token;
                firstToken = false;
            }
            else
            {
                command->addArgument(token);
            }

            token = "";
        }
        else
        {
            if(inputString[i] == '\"' )
            {
                i++;
                while( inputString[i] != '\"' )
                {
                    token += inputString[i];
                    i++;
                }
            }
            else
            {
                token += inputString[i];
            }
        }
    }

    return command;
}