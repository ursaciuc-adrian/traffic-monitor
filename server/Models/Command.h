#pragma once

#include <vector>
#include <string>
#include "Argument.h"

class Command {
private:
    std::vector<Argument*> m_arguments;

public:
    std::string value;

    Command() = default;;
    explicit Command(std::string command);

    void addArgument(std::string arg);
    void processArguments();
    const Argument * getArgument(unsigned long index) const;
};
