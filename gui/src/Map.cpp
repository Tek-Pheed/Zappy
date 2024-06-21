/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Map
*/

#include "Map.hpp"

Zappy::Map::Map()
{
}

Zappy::Map::~Map()
{
    while (!_bloc.empty())
        _bloc.pop_back();
}

void Zappy::Map::setX(int x)
{
    _x = x;
}

void Zappy::Map::setY(int y)
{
    _y = y;
}

int Zappy::Map::getX()
{
    return _x;
}

int Zappy::Map::getY()
{
    return _y;
}

std::list<Zappy::Bloc *> Zappy::Map::getBloc()
{
    return _bloc;
}

void Zappy::Map::setBloc(std::list<Zappy::Bloc *> blocs)
{
    _bloc = blocs;
}

void Zappy::Map::pushBloc(Bloc *bloc)
{
    _bloc.push_back(bloc);
}

void Zappy::Map::popBloc()
{
    while (!_bloc.empty()) {
        delete _bloc.front();
        _bloc.pop_front();
    }
}

Zappy::Bloc *Zappy::Map::getBloc(int x, int y)
{
    for (auto i : _bloc) {
        if (i->getX() == x && i->getY() == y)
            return (i);
    }
    return (nullptr);
}