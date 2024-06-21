/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Player.cpp
*/

#include <mutex>
#include <string>
// #include <raymath.h>
#include "Player.hpp"
#include "RessourcePool.hpp"

Zappy::Player::Player()
{
}

Zappy::Player::Player(const Zappy::Player &player)
{
    _model = player._model;
    _position = player._position;
    _inventory = player._inventory;
    _playerId = player._playerId;
    _x = player._x;
    _y = player._y;
    _orien = player._orien;
    _id = player._id;
}

Zappy::Player &Zappy::Player::operator=(const Zappy::Player &player)
{
    _model = player._model;
    _position = player._position;
    _inventory = player._inventory;
    _playerId = player._playerId;
    _x = player._x;
    _y = player._y;
    _orien = player._orien;
    _id = player._id;
    return (*this);
}

Zappy::Player::~Player()
{
}

void Zappy::Player::setPositionX(int x)
{
    std::unique_lock lock(_mut);
    this->_x = x;
}

int Zappy::Player::getPositionX()
{
    std::unique_lock lock(_mut);
    return this->_x;
}

void Zappy::Player::setPositionY(int y)
{
    std::unique_lock lock(_mut);
    this->_y = y;
}

int Zappy::Player::getPositionY()
{
    std::unique_lock lock(_mut);
    return this->_y;
}

void Zappy::Player::setPosition(std::map<std::string, int> position)
{
    std::unique_lock lock(_mut);
    _position = position;
}

std::map<std::string, int> Zappy::Player::getPosition()
{
    std::unique_lock lock(_mut);
    return _position;
}

void Zappy::Player::setInventory(std::map<std::string, int> inventory)
{
    std::unique_lock lock(_mut);
    _inventory = inventory;
}

void Zappy::Player::setPositionN(int orien)
{
    std::unique_lock lock(_mut);
    this->_orien = orien;
}

int Zappy::Player::getPositionN()
{
    std::unique_lock lock(_mut);
    return this->_orien;
}

void Zappy::Player::setID(int id)
{
    std::unique_lock lock(_mut);
    this->_id = id;
}

int Zappy::Player::getID()
{
    std::unique_lock lock(_mut);
    return this->_id;
}

std::mutex &Zappy::Player::getMutex()
{
    return (_mut);
}

void Zappy::Player::createModel(
    RessourceManager &objectPool, const std::string &modelPath)
{
    std::unique_lock lock(_mut);
    _model = objectPool.models.dynamicLoad("player", modelPath.c_str());
}

void Zappy::Player::displayPlayer(RessourceManager &objPool)
{
    Vector3 pos = {getPositionX() * 5.0f, 1.5f, getPositionY() * 5.0f};
    std::unique_lock lock(_mut);
    Model player = objPool.models.dynamicLoad("player", "assets/korok.obj");
    float rot = 270.0f;
    switch (_orien) {
        case 1: rot -= 270.0f; break;
        case 2: rot += 180.0f; break;
        case 3: rot += 90.0f; break;
        case 4: rot -= 0.0f; break;
        default: break;
    }
    // player.transform = MatrixRotateXYZ((Vector3){0.0f, DEG2RAD * rot,
    // 0.0f}); DrawModel(player, pos, 5.0f, WHITE);
    DrawModelEx(player, pos, (Vector3){0.0f, 1.5f, 0.0f}, rot,
        (Vector3){2.5f, 2.5f, 2.5f}, WHITE);
}
