/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Server.cpp
*/

#include <iostream>
#include <cstring>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/ServerData.hpp"

Zappy::Server::Server(int port, char *ip)
{
    _isconnect = false;
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(port);
    char buffer[1025];

    _buffer = buffer;
    inet_pton(AF_INET, ip, &_server_addr.sin_addr) <= 0;
    int result = connect(_sock, (struct sockaddr*)&_server_addr, sizeof(_server_addr)); //class error
    printf("%i\n", result);
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

std::queue<std::string> Zappy::Server::splitData(std::string data)
{
    std::queue<std::string> tmpQueue;
    std::stringstream ss(data);
    std::string word;

    printf("%s\n", data);
    while (ss >> word) {
        tmpQueue.push(word);
    }
    return tmpQueue;
}

void Zappy::Server::parseBuffer()
{
    // std::string buffer(_buffer);
    std::stringstream c(_buffer);
    std::string data;

    while (std::getline(c, data)) {
        if (!data.empty()) {
            _data.push(splitData(data));
        }
    }
}

void Zappy::Server::receiveMess()
{
    int bit_read = 0;

    FD_SET(_sock, &_readfds);
    int res = select(_sock + 1, &_readfds, &_writefds, nullptr, nullptr); //class error
    if (FD_ISSET(_sock, &_readfds)){
        bit_read = read(_sock, _buffer, 1024);
        printf("%i\n", bit_read);
        parseBuffer();
    }
}

std::queue<std::queue<std::string>> Zappy::Server::getData()
{
    return _data;
}
