/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** VectorPlayers.cpp
*/

#include "Player.hpp"

Zappy::Players::Players()
{
}

Zappy::Players::~Players()
{
}

void Zappy::Players::mapPlayers(Player *player)
{
    _players[player->getID()] = player;
}

std::map<int, Zappy::Player *> Zappy::Players::getPlayers()
{
    return _players;
}
