/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#pragma once

#include <map>
#include <raylib.h>
#include <string>
#include <vector>
#include "RessourcePool.hpp"

namespace Zappy
{
    class Player {
      public:
        Player();
        ~Player();
        std::map<std::string, int> getPosition();
        void setPosition(std::map<std::string, int>);
        void setPositionX(int x);
        int getPositionX();
        void setPositionY(int y);
        int getPositionY();
        void setPositionN(int north);
        int getPositionN();
        void setID(int id);
        int getID();
        void createModel(RessourceManager &objectPool, const std::string &modelPath);
        std::vector<std::map<std::string, int>> getInventory();
        void setInventory(std::map<std::string, int> inventory);
        void displayPlayer(RessourceManager &objPool);

      private:
        Model _model;
        std::map<std::string, int> _position;
        std::map<std::string, int> _inventory;
        int _playerId;
        int _x;
        int _y;
        int _orien;
        int _id;
    };

    class Players {
      private:
        std::map<int, Player *> _playerslist;

      public:
        Players();
        ~Players();
        void mapPlayers(Player *player);
        std::map<int, Player *> getPlayersList();
        void setPlayersList(std::map<int, Player *> playerslist);
    };
} // namespace Zappy
