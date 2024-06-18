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
    _playerslist[player->getID()] = player;
}

std::map<int, Zappy::Player *> Zappy::Players::getPlayersList()
{
    return _playerslist;
}

void Zappy::Players::setPlayersList(std::map<int, Zappy::Player *> playerlist)
{
    _playerslist = playerlist;
}
