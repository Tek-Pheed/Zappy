/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Mendiane.cpp
*/

#include "IItems.hpp"

Zappy::Mendiane::Mendiane(float density, std::map<std::string, int> position,
    std::vector<std::map<std::string, int>> sameItems, const char *model,
    const char *texture, Utils &u)
    : AItems(density, position, sameItems, model, texture, u)
{
}

Zappy::Mendiane::~Mendiane()
{
}
