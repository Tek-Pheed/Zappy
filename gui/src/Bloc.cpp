/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Bloc.cpp
*/

#include <mutex>
#include <cmath>
#include <raylib.h>
#include "Items.hpp"
#include "Map.hpp"

Zappy::Bloc::Bloc(int x, int y) : _x(x), _y(y)
{
}

Zappy::Bloc::~Bloc()
{
}

int Zappy::Bloc::getX()
{
    std::unique_lock lock(_mut);
    return this->_x;
}

int Zappy::Bloc::getY()
{
    std::unique_lock lock(_mut);
    return this->_y;
}

void Zappy::Bloc::setX(int x)
{
    std::unique_lock lock(_mut);
    this->_x = x;
}

void Zappy::Bloc::setY(int y)
{
    std::unique_lock lock(_mut);
    this->_y = y;
}

std::vector<Zappy::Player> Zappy::Bloc::getPlayers()
{
    std::unique_lock lock(_mut);
    return this->_players;
}

void Zappy::Bloc::setPlayers(std::vector<Zappy::Player> players)
{
    std::unique_lock lock(_mut);
    this->_players.clear();
    this->_players = players;
}

void Zappy::Bloc::addItem(Zappy::items item, size_t quantity)
{
    std::unique_lock lock(_mut);
    if (_items.find(item) == _items.end())
        _items[item] = 0;
    _items[item] += quantity;
}

void Zappy::Bloc::removeItem(Zappy::items item, size_t quantity)
{
    std::unique_lock lock(_mut);
    if (_items.find(item) == _items.end())
        return;
    _items[item] -= quantity;
    if (_items[item] == 0)
        _items.erase(item);
}

void Zappy::Bloc::setItems(std::vector<Zappy::items> items)
{
    _mut.lock();
    _items.clear();
    _mut.unlock();
    for (size_t i = 0; i != items.size(); i++)
        addItem(items[i], 1);
}

std::vector<Zappy::items> Zappy::Bloc::getItems()
{
    std::unique_lock lock(_mut);
    std::vector<Zappy::items> vect;

    vect.reserve(_items.size());
    for (auto &[key, value] : _items) {
        for (size_t i = 0; i != value; i++) {
            vect.emplace_back(key);
        }
    }
    return (vect);
}

Vector3 getItemPosition(Vector3 &bloc_pos, int nbItems, int index)
{
    size_t gridSize = std::sqrt(nbItems);
    Vector3 position = {0, 1.5, 0};
    size_t counter = 0;
    float step = 1.0f / (float) gridSize;

    for (int i = 0; i < nbItems; i++) {
        if (counter == gridSize) {
            position.z += step;
            position.x = 0;
            counter = 0;
        }
        if (i == index)
            break;
        position.x += step;
        counter++;
    }
    position.x += bloc_pos.x;
    position.z += bloc_pos.z;
    if (gridSize > 1) {
        position.x -= (gridSize / 2.0f) * step;
        position.z -= (gridSize / 2.0f) * step;
    }
    return (position);
}

void Zappy::Bloc::display(RessourceManager &objectPool)
{
    Model water = objectPool.models.dynamicLoad("water", "assets/water.obj");
    Model island =
        objectPool.models.dynamicLoad("island", "assets/island.obj");
    Vector3 pos = {(getX() * 5.0f), 1.5f, (getY() * 5.0f)};
    Vector3 Ipos;
    std::vector<Zappy::items> items = getItems();
    size_t i = 0;

    DrawModel(
        water, (Vector3){getX() * 5.0f, 0.0f, getY() * 5.0f}, 0.5f, WHITE);
    DrawModel(
        island, (Vector3){getX() * 5.0f, 0.0f, getY() * 5.0f}, 0.5f, WHITE);
    for (const auto &item : items) {
        Ipos = getItemPosition(pos, items.size(), i);
        DrawModel(objectPool.models.getRessource(Zappy::itemNames[item]), Ipos,
            1.0f, WHITE);
        i++;
    }
}
