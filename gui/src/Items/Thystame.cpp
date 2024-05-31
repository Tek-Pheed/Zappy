/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Thystame.cpp
*/

#include "IItems.hpp"

Zappy::Thystame::Thystame(float density, std::map<std::string, int> position,
    std::vector<std::map<std::string, int>> sameItems, const char *model,
    const char *texture, Utils &u)
    : AItems(density, position, sameItems, model, texture, u)
{
}

Zappy::Thystame::~Thystame()
{
}
