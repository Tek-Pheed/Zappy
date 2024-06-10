/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#pragma once
#include <vector>
#include "IItems.hpp"


namespace Zappy {
class Map {
    public:
        Map(int x, int y);
        ~Map();

    protected:
    private:
};

class Bloc {
    public:
        Bloc(int x, int y, std::vector<IItems *> items);
        ~Bloc();
    protected:
    private:
        int _x;
        int _y;
        std::vector<IItems *> _items;
};
}
