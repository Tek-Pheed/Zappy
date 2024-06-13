/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Food.cpp
*/

#include "Items.hpp"

Zappy::Food::Food(/*std::vector<std::map<std::string, int>> sameItems,*/
    const char *model, const char *texture, Utils &u)
    : AItems(model, texture, u)
{
}

Zappy::Food::~Food()
{
}
