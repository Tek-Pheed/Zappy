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
#include "Map.hpp"
#include "Player.hpp"

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
        std::vector<IItems *> createItems(std::queue<std::string> items);
        Bloc *createBloc(std::queue<std::string> bloc);
        void createMap(std::queue<std::string> size, Map realmap);
        void createTeams(std::queue<std::string> teams);
        int createFrequ(std::queue<std::string> freq);
        void parsing(std::queue<std::queue<std::string>> data);
        void newPlayer(std::queue<std::string> player, Player realplayer);
        void positionPlayer(std::queue<std::string> player, Player realplayer);
        void levelPlayer(std::queue<std::string> player);
        void inventoryPlayer(std::queue<std::string> player);
        void expulsion(std::queue<std::string> exp);
        void broadcast(std::queue<std::string> broad);
        void startInc(std::queue<std::string> inc);
        void endInc(std::queue<std::string> inc);
        void layingEgg(std::queue<std::string> egg);
        void dropRess(std::queue<std::string> ress);
        void collectRess(std::queue<std::string> ress);
        void death(std::queue<std::string> player);
        void laidEgg(std::queue<std::string> egg);
        void connectEgg(std::queue<std::string> egg);
        void deathEgg(std::queue<std::string> egg);
        void frequModification(std::queue<std::string> freq);
        void endGame(std::queue<std::string> team);
        void messServer(std::queue<std::string> mess);
        void unknowCommand();
        //sbp
    };
} // namespace Zappy
