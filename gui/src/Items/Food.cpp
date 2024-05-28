/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Food.cpp
*/

#include "IItems.hpp"

Zappy::Food::Food(float density, std::map<std::string, int> position, std::vector<std::map<std::string, int>> sameItems) : Atems(density, position, sameItems)
{

}

Zappy::Food::~Food()
{

}
