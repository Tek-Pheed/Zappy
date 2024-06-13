/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** AItems.cpp
*/

#include "Items.hpp"

Zappy::AItems::AItems(/*std::vector<std::map<std::string, int>> sameItems,*/
    const char *model, const char *texture, Utils &u)
    : _u(u)
{
    _model = _u.createModel(texture, model);
}

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

void Zappy::AItems::setModel(const char *texture, const char *model)
{
    _model = _u.createModel(model, texture);
}

Model Zappy::AItems::getModel()
{
    return _model;
}
