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
#include "Items.hpp"


namespace Zappy {

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
