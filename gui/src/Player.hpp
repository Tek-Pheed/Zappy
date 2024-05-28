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

namespace Zappy { 
class Player {
    public:
        Player();
        ~Player();
        std::map<std::string, int> getPosition();
        void setPosition(std::map<std::string, int>);
        void setPositionX(int x);
        void setPositionY(int y);
        std::vector <std::map<std::string, int>> getInventory();
        void setInventory(std::map<std::string, int> inventory);

    protected:
    private:
        std::map<std::string, int> _position;
        std::map<std::string, int> _inventory;
        int _playerId;
};
}
