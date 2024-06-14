/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** AItems.cpp
*/

#include "Items.hpp"

Zappy::AItems::AItems(Zappy::items item): _item(item) {}

Zappy::AItems::~AItems() {}

Zappy::items Zappy::AItems::getItem()
{
    return this->_item;
}
