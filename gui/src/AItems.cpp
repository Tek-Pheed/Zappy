/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** AItems.cpp
*/

#include "Items.hpp"

Zappy::AItems::AItems(Model model) : _model(model) {}

Zappy::AItems::~AItems()
{
}

// void Zappy::AItems::addSameItems(std::map<std::string, int> position)
// {
//     _sameItems.push_back(position);
// }

// std::vector<std::map<std::string, int>> Zappy::AItems::getSameItems()
// {
//     return _sameItems;
// }

Model Zappy::AItems::getModel()
{
    return _model;
}
