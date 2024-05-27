/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <map>
#include <vector>
#include <string>

class Player {
    public:
        Player();
        ~Player();
        std::map<std::string, int> getPosition();
        void setPosition(pos: std::map<std::string, int>);
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

#endif /* !PLAYER_HPP_ */
