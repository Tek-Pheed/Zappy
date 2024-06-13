/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Player.cpp
*/

#include "Player.hpp"

Zappy::Player::Player()
{
}

Zappy::Player::~Player()
{
}

void Zappy::Player::setPositionX(int x)
{
    _x = x;
}

int Zappy::Player::getPositionX()
{
    return _x;
}

void Zappy::Player::setPositionY(int y)
{
    _y = y;
}

int Zappy::Player::getPositionY()
{
    return _y;
}

void Zappy::Player::setPosition(std::map<std::string, int> position)
{
    _position = position;
}

std::map<std::string, int> Zappy::Player::getPosition()
{
    return _position;
}

void Zappy::Player::setInventory(std::map<std::string, int> inventory)
{
    _inventory = inventory;
}
