#pragma once

#include <unistd.h>
#include <string>
#include <string.h>
#include <vector>
#include <netinet/in.h>

static void NormalizeString(std::string &str)
{
    if (str[str.length() - 1] == '\n')
    {
        str = str.substr(0, str.length() - 1);
    }
}

static int Write(int socket, std::string &str)
{
    NormalizeString(str);

    unsigned long length = str.length();
    if(write(socket, &length, sizeof(length)) == -1)
    {
        return -1;
    }

    if(write(socket, str.c_str(), length) == -1)
    {
        return -1;
    }

    return 1;
}

static int Read(int socket, std::string &str)
{
    unsigned long length;
    int bytes;

    if(socket == 0)
    {
        length = 1024;
    }
    else
    {
        if((bytes = read(socket, &length, sizeof(length))) == -1)
        {
            return -1;
        }

        if(bytes == 0)
        {
            return 0;
        }
    }

    char buf[length + 1];
    bzero(buf, length + 1);

    if((bytes = read(socket, &buf, length)) == -1)
    {
        return -1;
    }

    if(bytes == 0)
    {
        return 0;
    }

    str.assign(buf);
    NormalizeString(str);

    return 1;
}

static int CreateSocket()
{
    int sd;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error occured while creating the socket.\n");
    }

    return sd;
}
