/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** egg
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "server.h"

egg_t *create_egg(int x, int y, team_t *team)
{
    static int nb = 0;
    egg_t *egg = NULL;

    egg = calloc(1, sizeof(egg_t));
    egg->team = team;
    egg->x = x;
    egg->y = y;
    egg->number = nb;
    nb += 1;
    return (egg);
}

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
            new_egg =
                create_egg(rand() % serv->resX, rand() % serv->resY, team);
            list_add_elem_at_back(&team->eggs, new_egg);
        }
    }
}
