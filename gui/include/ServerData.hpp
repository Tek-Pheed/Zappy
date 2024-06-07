/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ServerData
*/

#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <queue>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace Zappy
{
    class Server {
      private:
        int _sock;
        fd_set _readfds;
        fd_set _writefds;
        bool _isconnect;
        struct sockaddr_in _server_addr;
        std::queue<std::queue<std::string>> _data;

      public:
        Server(int port, char *ip);
        ~Server();
        bool getIsconnect();
        void receiveMess();
        void messConnect();
        void parseBuffer(char *buffer);
        std::queue<std::string> splitData(std::string data);
        std::queue<std::queue<std::string>> getData();
        void popData();
    };

    class Parser {
      private:
      public:
        void createItems();
        void createmap();
    };
} // namespace Zappy
