/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Linemate.cpp
*/

#include "Items.hpp"

Zappy::Linemate::Linemate(/*std::vector<std::map<std::string, int>> sameItems,*/
    const char *model, const char *texture, Utils &u)
    : AItems(model, texture, u)
{
}

Zappy::Linemate::~Linemate()
{
}
