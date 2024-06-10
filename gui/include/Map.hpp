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
#include "IItems.hpp"


namespace Zappy {

class Map {
    public:
        Map(int x, int y) : _x(x), _y(y) {}
        ~Map() {}
        void getBlock(std::list<Bloc>& block) const;
        std::list<Bloc> setBlock(const std::list<Bloc>& block);
        void drawMap();

    private:
        int _x;
        int _y;
        std::list<Bloc> _block;
};

class Bloc {
    public:
        Bloc(int x, int y, std::vector<IItems *> items);
        ~Bloc();
    protected:
    private:
        int _x;
        int _y;
};
}
