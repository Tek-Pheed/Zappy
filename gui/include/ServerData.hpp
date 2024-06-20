/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ServerData
*/

#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
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
        Server();
        ~Server();
        void init_connection(std::string ip, int port);
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
        std::vector<Zappy::items> createItems(std::queue<std::string> items);
        Bloc *createBloc(std::queue<std::string> bloc);
        void createMap(std::queue<std::string> size, Map realmap);
        void createMap(std::queue<std::string> size);
        void createTeams(std::queue<std::string> teams);
        int createFrequ(std::queue<std::string> freq);
        void parsing(RessourceManager &objectPool, std::queue<std::queue<std::string>> data);
        Player *newPlayer(RessourceManager &objectPool, std::queue<std::string> player);
        void positionPlayer(std::queue<std::string> player);
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

        Map getMap();
        void setMap(Map map);
        Players getPlayersList();
        void setPlayersList(Players list);

        private:
          Map _map;
          Players _playersMap;
          //std::vector<IItems *> _items;
          std::vector<Model> _itemsModelList;
    };
} // namespace Zappy
