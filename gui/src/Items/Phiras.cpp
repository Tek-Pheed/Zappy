/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Phiras.cpp
*/

#include "IItems.hpp"

Zappy::Phiras::Phiras(float density, std::map<std::string, int> position, std::vector<std::map<std::string, int>> sameItems,
    std::string model, std::string texture, Utils u) : Atems(density, position, sameItems, model, texture, u)
{

}
