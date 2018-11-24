
#include <netinet/in.h>
#include <vector>

class Server
{
private:
    std::vector<struct sockaddr_in> clients;

    void Listen(int queueSize);
    void Bind();

public:
    struct sockaddr_in server;
    int socket;

    explicit Server(int socket, int port, int queueSize);
    int AddClient();

    ~Server();
};