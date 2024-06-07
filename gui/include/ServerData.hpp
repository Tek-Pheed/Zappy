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
#include <list>
#include <queue>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include "Items.hpp"

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
        Parser();
        ~Parser();
        std::list<IItems> createItems(std::queue<std::string> items);
        void createBloc(std::queue<std::string> bloc);
        void createMap(std::queue<std::string> size);
        void createTeams(std::queue<std::string> teams);
        void createFrequ(std::queue<std::string> freq);
        void parsing(std::queue<std::queue<std::string>> data);
    };
} // namespace Zappy
