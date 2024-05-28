/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Atems.cpp
*/

#include "IItems.hpp"

Zappy::Atems::Atems(float density, std::map<std::string, int> position, std::vector<std::map<std::string, int>> sameItems)
{
    _density = density;
    _position = position;
    _sameItems = sameItems;
}

Zappy::Atems::~Atems()
{

}

void Zappy::Atems::setDensity(float density)
{
    _density = density;
}

void Zappy::Atems::setPosition(std::map<std::string, int> position)
{
    _position = position;
}

void Zappy::Atems::addSameItems(std::map<std::string, int> position)
{
    _sameItems.push_back(position);
}

float Zappy::Atems::getDensity()
{
    return _density;
}

std::map<std::string, int> Zappy::Atems::getPosition()
{
    return _position;
}

std::vector<std::map<std::string, int>> Zappy::Atems::getSameItems()
{
    return _sameItems;
}
