
#include <netinet/in.h>
#include <vector>

class Server
{
private:
    struct sockaddr_in server;
    std::vector<struct sockaddr_in> clients;

public:
    explicit Server(int port);
    int AddClient(int socket);

    ~Server();
};