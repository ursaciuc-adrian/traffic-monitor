#include <utility>

#include "Command.h"
#include "Argument.h"

Command::Command(std::string command)
{
    this->value = std::move(command);
}

void Command::addArgument(std::string arg)
{
    this->m_arguments.push_back(new Argument(std::move(arg)));
}

const Argument * Command::getArgument(unsigned long index) const
{
    if(m_arguments.size() > index)
    {
        return m_arguments.at(index);
    }

    return nullptr;
}

void Command::processArguments()
{
    for (auto c: this->m_arguments)
    {
        if(c->getValue()[0] == '"')
        {

        }
    }
}
