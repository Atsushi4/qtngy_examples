#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <string>

class TcpSocket
{
public:
    TcpSocket();

public:
    bool connect(const std::string &remoteAddress, int port);
    bool send(const std::string &message);

private:
    int sock;
};

#endif // TCPSOCKET_H
