#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <CommunicationHelper.h>
#include <iostream>

#include "Models/Client.h"
#include "Response.h"

int main (int argc, char *argv[])
{
    Client *client;

    int sd;			// descriptorul de socket
    struct sockaddr_in server{};	// structura folosita pentru conectare
    std::string msg;		// mesajul trimis

    /* exista toate argumentele in linia de comanda? */
    if (argc != 3)
    {
        printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
        return -1;
    }
    client = new Client(argv[1], std::stoi(argv[2]));


    /* cream socketul */
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror ("Eroare la socket().\n");
        return errno;
    }

    /* umplem structura folosita pentru realizarea conexiunii cu serverul */
    /* familia socket-ului */
    server.sin_family = AF_INET;
    /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr(client->GetIp().c_str());
    /* portul de conectare */
    server.sin_port = htons (static_cast<uint16_t>(client->GetPort()));

    /* ne conectam la server */
    if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
        perror ("[client]Eroare la connect().\n");
        return errno;
    }

    int parent = Fork();

    if (parent)
    {
        std::string command;
        while(true)
        {
            std::getline(std::cin, command);
            Write(sd, command);
            std::cout<<"ai introdus "<< command <<std::endl;

            if(command == "quit")
            {
                exit(0);

                break;
            }
        }
    }
    else
    {
        while(true)
        {
            Read(sd, msg);
            std::cout << msg << std::endl;

            if(msg == "quit")
            {
                break;
            }
        }
        exit(0);
    }

    close (sd);

    return 0;
}
