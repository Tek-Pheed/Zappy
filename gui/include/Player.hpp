/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#pragma once

#include <map>
#include <vector>
#include <string>
#include <raylib.h>

namespace Zappy { 
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
        void setPositionS(int south);
        int getPositionS();
        void setPositionW(int west);
        int getPositionW();
        void setPositionE(int est);
        int getPositionE();
        void setID(int id);
        int getID();
        void createModel(std::string modelPath);
        std::vector <std::map<std::string, int>> getInventory();
        void setInventory(std::map<std::string, int> inventory);

    protected:
    private:
        Model _model;
        std::map<std::string, int> _position;
        std::map<std::string, int> _inventory;
        int _playerId;
        int _x;
        int _y;
        int _south;
        int _north;
        int _est;
        int _west;
        int _id;
};

class Players
{
private:
    std::map<int, Player *> _players;
public:
    Players();
    ~Players();
    void mapPlayers(Player *player);
    std::map<int, Player *> getPlayers();
};
}
