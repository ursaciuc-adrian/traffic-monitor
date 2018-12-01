#pragma once

#include <unistd.h>
#include <string>
#include <vector>
#include <netinet/in.h>

static int Write(int socket, const std::string &str)
{
    /*unsigned long length = str.length();
    if(write(socket, &length, sizeof(length)) == -1)
    {
        perror("erroare la write");
        return -1;
    }

    if(write(socket, str.c_str(), length) == -1)
    {
        perror("erroare la write");

        return -1;
    }*/

    write(socket, str.c_str(), 100);
    return 0;
}

static int Read(int socket, std::string &str)
{
    /*unsigned long length;
    if(read(socket, &length, sizeof(length)) == -1)
    {
        perror("erroare la read");

        return -1;
    }

    std::vector<char> buffer(length + 1);
    if(read(socket, buffer.data(), length) == -1)
    {
        perror("erroare la read");

        return -1;
    }

    buffer[length] = '\0';
    str = buffer.data();
*/

    char buf[200];
    read(socket, buf, 200);

    std::string resp(buf);
    str = resp;

    return 0;
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

static int Fork()
{
    int f;

    if((f = fork()) == -1)
    {
        perror("Error at fork().\n");
        exit(0);
    }

    return f;
}