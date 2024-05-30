/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ServerData
*/

#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

namespace Zappy {
class Server
{
private:
    int _sock;
    std::string _buffer;
    fd_set _readfds;
    fd_set _writefds;
    bool _isconnect;
    struct sockaddr_in _server_addr;
public:
    Server(int port, char *ip);
    ~Server();
    bool getIsconnect();
    void receiveMess();
    void parseBuffer();
};
}
