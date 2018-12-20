#pragma once

#include "Argument.h"

Argument::Argument(std::string arg)
{
    this->m_value = std::move(arg);
}

std::string Argument::getValue() const
{
    return this->m_value;
}
