#include "tcpsocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

TcpSocket::TcpSocket()
    : sock(0)
{
}

bool TcpSocket::connect(const std::string &remoteAddress, int port)
{
    sockaddr_in server;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr
            = *(unsigned int*)gethostbyname(remoteAddress.c_str())->h_addr_list[0];
    ::connect(sock, (struct sockaddr*)&server, sizeof(server));
    return true;
}

bool TcpSocket::send(const std::string &message)
{
    write(sock, message.c_str(), message.size() + 1);
    return true;
}
