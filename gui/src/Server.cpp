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
#include "ServerData.hpp"

Zappy::Server::Server() {}

bool Zappy::Server::getIsconnect()
{
    return _isconnect;
}

Zappy::Server::~Server()
{
    close(_sock);
}

void Zappy::Server::init_connection(std::string ip, int port)
{
    _isconnect = false;
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(port);
    if (ip == "localhost")
        ip = "127.0.0.1";
    inet_pton(AF_INET, ip.c_str(), &_server_addr.sin_addr);
    int result = connect(_sock, (struct sockaddr*)&_server_addr, sizeof(_server_addr)); //class error
    if (result == -1) {
        std::cerr << "Connection error" << std::endl;
    } else {
        _isconnect = true;
    }
    FD_ZERO(&_writefds);
    FD_ZERO(&_readfds);
}

std::queue<std::string> Zappy::Server::splitData(std::string data)
{
    std::queue<std::string> tmpQueue;
    std::stringstream ss(data);
    std::string word;

    while (ss >> word) {
        //std::cout << word << std::endl;
        tmpQueue.push(word);
    }
    //std::cout << tmpQueue.front() << std::endl;
    return tmpQueue;
}

void Zappy::Server::messConnect()
{
    std::string message = "GRAPHIC";

    //FD_SET(_sock, &_writefds);
    //int res = select(_sock + 1, &_readfds, &_writefds, nullptr, nullptr); //class error
    //if (FD_ISSET(_sock, &_writefds)){
    //    write(_sock, message.c_str(), message.length());
    //}
    send(_sock, message.c_str(), message.length(), 0);
}

void Zappy::Server::parseBuffer(char *buffer)
{
    std::stringstream c(buffer);
    std::string data;

    while (std::getline(c, data)) {
        if (!data.empty()) {
            std::queue<std::string> response = splitData(data);
            _data.push(response);
            std::cout << _data.front().front() << std::endl;
        }
    }
}

void Zappy::Server::receiveMess()
{
    int bit_read = 0;
    char buffer[10024];

    FD_SET(_sock, &_readfds);
    select(_sock + 1, &_readfds, &_writefds, nullptr, nullptr); //class error
    if (FD_ISSET(_sock, &_readfds)){
        bit_read = read(_sock, buffer, 10023);
        buffer[bit_read] ='\0';
        parseBuffer(buffer);
        memset(buffer, 0, sizeof(buffer));
    }
}

void Zappy::Server::popData()
{
    _data.pop();
}

std::queue<std::queue<std::string>> Zappy::Server::getData()
{
    return _data;
}
