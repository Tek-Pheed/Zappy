/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** egg
*/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "server.h"

void create_teams_eggs(server_t *serv)
{
    size_t nb_teams = list_get_size(serv->teams);
    team_t *team = NULL;
    egg_t *new_egg = NULL;

    for (size_t i = 0; i != nb_teams; i++) {
        team = list_get_elem_at_position(serv->teams, i);
        if (team == NULL)
            continue;
        for (size_t e = 0; e != (size_t) serv->clientNb; e++) {
            new_egg = calloc(1, sizeof(egg_t));
            new_egg->x = rand() % serv->resX;
            new_egg->y = rand() % serv->resY;
            new_egg->team = team;
            list_add_elem_at_back(&team->eggs, new_egg);
        }
    }
}
