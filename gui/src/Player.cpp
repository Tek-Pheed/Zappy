/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Player.cpp
*/

#include <string>
// #include <raymath.h>
#include "RessourcePool.hpp"
#include "Player.hpp"

Zappy::Player::Player()
{
}

Zappy::Player::~Player()
{
}

void Zappy::Player::setPositionX(int x)
{
    this->_x = x;
}

int Zappy::Player::getPositionX()
{
    return this->_x;
}

void Zappy::Player::setPositionY(int y)
{
    this->_y = y;
}

int Zappy::Player::getPositionY()
{
    return this->_y;
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
    this->_orien = orien;
}

int Zappy::Player::getPositionN()
{
    return this->_orien;
}

void Zappy::Player::setID(int id)
{
    this->_id = id;
}

int Zappy::Player::getID()
{
    return this->_id;
}

void Zappy::Player::createModel(
    RessourceManager &objectPool, const std::string &modelPath)
{
    _model = objectPool.models.dynamicLoad("player", modelPath.c_str());
}

void Zappy::Player::displayPlayer(RessourceManager &objPool)
{
    Model player = objPool.models.dynamicLoad("player", "assets/korok.obj");
    Vector3 pos = {getPositionX() * 5.0f, 1.5f, getPositionY() * 5.0f};
    float rot = 270.0f;
    switch (_orien) {
            case 1: rot -= 270.0f; break;
            case 2: rot += 180.0f; break;
            case 3: rot += 90.0f; break;
            case 4: rot -= 0.0f; break;
            default: break;
    }
    // player.transform = MatrixRotateXYZ((Vector3){0.0f, DEG2RAD * rot, 0.0f});
    // DrawModel(player, pos, 5.0f, WHITE);
    DrawModelEx(player, pos, (Vector3){0.0f, 1.0f, 0.0f}, rot, (Vector3){5.0f, 5.0f, 5.0f}, WHITE);
}
