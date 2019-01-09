#ifndef _LOGGER_H
#define _LOGGER_H

class Logger
{
public:
    static void LogError(std::string message)
    {
        std::cout << "\x1b[5m\x1b[31m" + message + "\x1b[0m" << std::endl;
    }

    static void LogMessage(std::string message)
    {
        std::cout << "\x1b[5m\x1b[33m" + message + "\x1b[0m" << std::endl;
    }
};

#endif


