/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Bloc.cpp
*/

#include "Items.hpp"
#include "Map.hpp"

Zappy::Bloc::Bloc(int x, int y) : _x(x), _y(y)
{
}

Zappy::Bloc::~Bloc()
{
}

int Zappy::Bloc::getX() const
{
    return this->_x;
}

int Zappy::Bloc::getY() const
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

std::vector<Zappy::Player> Zappy::Bloc::getPlayers()
{
    return this->_players;
}

void Zappy::Bloc::setPlayers(std::vector<Zappy::Player> players)
{
    this->_players = players;
}

void Zappy::Bloc::addItem(Zappy::items item, size_t quantity)
{
    if (_items.find(item) == _items.end())
        _items[item] = 0;
    _items[item] += quantity;
}

void Zappy::Bloc::removeItem(Zappy::items item, size_t quantity)
{
    if (_items.find(item) == _items.end())
        return;
    _items[item] -= quantity;
    if (_items[item] == 0)
        _items.erase(item);
}

void Zappy::Bloc::setItems(std::vector<Zappy::items> items)
{
    for (size_t i = 0; i != items.size(); i++)
        addItem(items[i], 1);
}

std::vector<Zappy::items> Zappy::Bloc::getItems()
{
    std::vector<Zappy::items> vect;

    vect.reserve(_items.size());
    for (auto &[key, value] : _items) {
        for (size_t i = 0; i != value; i++) {
            vect.emplace_back(key);
        }
    }
    return (vect);
}

void Zappy::Bloc::display(RessourceManager &objectPool)
{
    Model water = objectPool.models.dynamicLoad("water", "assets/water.obj");
    Model island =
        objectPool.models.dynamicLoad("island", "assets/island.obj");
    Vector3 pos = {getX() * 5.0f, 1.0f, getY() * 5.0f};
    std::vector<Zappy::items> items = getItems();

    DrawModel(
        water, (Vector3){getX() * 5.0f, 0.0f, getY() * 5.0f}, 0.5f, WHITE);
    DrawModel(
        island, (Vector3){getX() * 5.0f, 0.0f, getY() * 5.0f}, 0.5f, WHITE);
    for (const auto &item : items) {
        DrawModel(
            objectPool.models.getRessource(Zappy::itemNames[item]), pos, 1.0f, WHITE);
        pos.y += 0.75f;
    }
}
