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
