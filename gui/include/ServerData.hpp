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
#include <queue>

namespace Zappy {
class Server
{
private:
    int _sock;
    char *_buffer;
    fd_set _readfds;
    fd_set _writefds;
    bool _isconnect;
    struct sockaddr_in _server_addr;
    std::queue<std::queue<std::string>> _data;
    void parseBuffer();
    std::queue<std::string> splitData(std::string data);
public:
    Server(int port, char *ip);
    ~Server();
    bool getIsconnect();
    void receiveMess();
    std::queue<std::queue<std::string>> getData();
};
}
