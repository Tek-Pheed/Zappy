/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <iostream>
#include <memory>
#include "Items.hpp"
#include "Player.hpp"


namespace Zappy {

class Bloc {
    public:
        Bloc(int x, int y, std::vector<IItems *> items);
        ~Bloc();
        int getX();
        int getY();
        void setX(int x);
        void setY(int y);
        std::vector<Zappy::IItems *> getItems();
        void setItems(std::vector<Zappy::IItems *> items);
        std::vector<Zappy::Player> getPlayers();
        void setPlayers(std::vector<Zappy::Player> players);

    private:
        int _x;
        int _y;
        std::vector<Zappy::IItems *> _items;
        std::vector<Zappy::Player> _players;
};

class Map {
    public:
        Map();
        ~Map();
        void pushBloc(Bloc *bloc);
        std::list<Bloc *> getBloc();
        void setBloc(std::list<Bloc *> blocs);
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();
        void drawMap();

    private:
        int _x;
        int _y;
        std::list<Bloc *> _bloc;
};
}
