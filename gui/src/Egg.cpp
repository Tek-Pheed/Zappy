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

void Zappy::Egg::displayEggs(RessourceManager &objPool)
{
    std::cout << "X: " << getX() << std::endl;
    Vector3 pos = {getX() * 5.0f, 1.5f, getY() * 5.0f};
    Model egg = objPool.models.dynamicLoad("egg", "assets/object/egg.obj");
    DrawModelEx(egg, pos, (Vector3){0.0f, 1.5f, 0.0f}, 0,
        (Vector3){10.0f, 10.0f, 10.0f}, WHITE);
}
