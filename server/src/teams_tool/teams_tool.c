/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** teams_tool
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

team_t *get_team_client(server_t *serv, client_t *cli)
{
    int len = list_get_size(serv->teams);
    team_t *tmp = NULL;

    for (int i = 0; i != len; i++) {
        tmp = list_get_elem_at_position(serv->teams, 1);
        if (strcmp(cli->team_name, tmp->name) == 0)
            return tmp;
    }
    return NULL;
}

int get_free_space_team(team_t *team)
{
    if (team == NULL)
        return (0);
    return list_get_size(team->eggs);
}
