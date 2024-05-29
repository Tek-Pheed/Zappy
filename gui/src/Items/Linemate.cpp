/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Linemate.cpp
*/

#include "IItems.hpp"

Zappy::Linemate::Linemate(float density, std::map<std::string, int> position,
           std::vector<std::map<std::string, int>> sameItems,
           const char *model, const char *texture, Utils &u) : Atems(density, position, sameItems, model, texture, u)
{

}

Zappy::Linemate::~Linemate()
{

}
