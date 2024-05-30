/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Server.cpp
*/

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "ServerData.hpp"

Zappy::Server::Server(int port, char *ip)
{
    _isconnect = false;
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(port);

    inet_pton(AF_INET, ip, &_server_addr.sin_addr) <= 0;
    int result = connect(_sock, (struct sockaddr*)&_server_addr, sizeof(_server_addr));
    FD_ZERO(&_writefds);
    FD_ZERO(&_readfds);
}

bool Zappy::Server::getIsconnect()
{
    return _isconnect;
}

Zappy::Server::~Server()
{
    close(_sock);
}
