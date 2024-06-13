/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Bloc.cpp
*/

#include "Map.hpp"

Zappy::Bloc::Bloc(int x, int y, std::vector<IItems *> items) : _x(x), _y(y), _items(items)
{
}

Zappy::Bloc::~Bloc()
{
}

int Zappy::Bloc::getX()
{
    return this->_x;
}

int Zappy::Bloc::getY()
{
    return this->_y;
}

void Zappy::Bloc::setX(int x)
{
    this->_x = x;
}

void Zappy::Bloc::setY(int y)
{
    this->_y = y;
}

std::vector<Zappy::IItems *> Zappy::Bloc::getItems()
{
    return this->_items;
}

void Zappy::Bloc::setItems(std::vector<Zappy::IItems *> items)
{
    this->_items = items;
}

