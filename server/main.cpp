#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <netinet/in.h>

#include "Models/Server.cpp"

#define PORT 2026

void proc_exit(int signo)
{
    pid_t pid;

    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0);
}

int main()
{
    char msg[100];             //mesajul primit de la client
    char msgrasp[100] = " "; //mesaj de raspuns pentru client
    int sd;                     //descriptorul de socket

    auto *server = new Server(PORT);
    /* crearea unui socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("[server]Eroare la socket().\n");
        return errno;
    }

    /* pregatirea structurilor de date */

    /* atasam socketul */
    if (bind(sd, (struct sockaddr *) &server->server, sizeof(struct sockaddr)) == -1)
    {
        perror("[server]Eroare la bind().\n");
        return errno;
    }

    /* punem serverul sa asculte daca vin clienti sa se conecteze */
    if (listen(sd, 5) == -1)
    {
        perror("[server]Eroare la listen().\n");
        return errno;
    }

    printf("[server]Asteptam la portul %d...\n", PORT);
    fflush(stdout);

    while (1)
    {
        /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
        int client = server->AddClient(sd);

        signal(SIGCHLD, proc_exit);
        switch (fork())
        {
            case -1:
                perror("main: fork");
                exit(0);
            case 0:

                /* eroare la acceptarea conexiunii de la un client */
                if (client < 0)
                {
                    perror("[server]Eroare la accept().\n");
                    continue;
                }

                /* s-a realizat conexiunea, se astepta mesajul */
                bzero(msg, 100);
                printf("[server]Asteptam mesajul...\n");
                fflush(stdout);

                /* citirea mesajului */
                if (read(client, msg, 100) <= 0)
                {
                    perror("[server]Eroare la read() de la client.\n");
                    close(client); /* inchidem conexiunea cu clientul */
                    continue;      /* continuam sa ascultam */
                }

                printf("[server]Mesajul a fost receptionat...%s\n", msg);

                /*pregatim mesajul de raspuns */
                bzero(msgrasp, 100);
                strcat(msgrasp, "Hello ");
                strcat(msgrasp, msg);

                printf("[server]Trimitem mesajul inapoi...%s\n", msgrasp);

                /* returnam mesajul clientului */
                if (write(client, msgrasp, 100) <= 0)
                {
                    perror("[server]Eroare la write() catre client.\n");
                    continue; /* continuam sa ascultam */
                } else
                    printf("[server]Mesajul a fost trasmis cu succes.\n");
                /* am terminat cu acest client, inchidem conexiunea */
                close(client);

                exit(0);
        }
    }
}
