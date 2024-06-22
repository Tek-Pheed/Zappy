/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Menu.cpp
*/

#include <mutex>
#include <cmath>
#include <raylib.h>
#include "Items.hpp"
#include "Map.hpp"

Zappy::Egg::Egg(int x, int y, int id) : _x(x), _y(y), _id(id)
{
}

Zappy::Egg::~Egg()
{
}

void Zappy::Egg::displayEggs(RessourceManager &objPool)
{

}

int Zappy::Egg::getID()
{
    return this->_id;
}

int Zappy::Egg::getX()
{
    return this->_x;
}

int Zappy::Egg::getY()
{
    return this->_y;
}