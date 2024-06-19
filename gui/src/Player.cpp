/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include <string>
#include "RessourcePool.hpp"

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

void Zappy::Player::setPositionN(int orien)
{
    _orien = orien;
}

int Zappy::Player::getPositionN()
{
    return _orien;
}

void Zappy::Player::setID(int id)
{
    _id = id;
}

int Zappy::Player::getID()
{
    return _id;
}

void Zappy::Player::createModel(
    RessourceManager &objectPool, const std::string &modelPath)
{
    _model = objectPool.models.dynamicLoad("player", modelPath.c_str());
}
