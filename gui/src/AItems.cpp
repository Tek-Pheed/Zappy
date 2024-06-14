/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** AItems.cpp
*/

#include "Items.hpp"

Zappy::AItems::AItems(Zappy::items item): _item(item) {}

Zappy::AItems::~AItems() {}

Zappy::items Zappy::AItems::getItem()
{
    return this->_item;
}

float Zappy::AItems::getX()
{
    return this->_x;
}

float Zappy::AItems::getZ()
{
    return this->_z;
}

void Zappy::AItems::setX(float x)
{
    this->_x = x;
}

void Zappy::AItems::setZ(float z)
{
    this->_z = z;
}
