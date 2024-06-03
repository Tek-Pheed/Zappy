/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** teams_tool
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "server.h"

team_t *team_get_client(server_t *serv, client_t *cli)
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

static bool team_can_add_player(const server_t *serv, team_t *team)
{
    size_t nb_eggs = list_get_size(team->eggs);

    if (nb_eggs == 0)
        return (false);
    if (team->nb_player >= serv->clientNb)
        return (false);
    return (true);
}

bool team_add_client(server_t *serv, client_t *client)
{
    size_t nb_teams = list_get_size(serv->teams);
    team_t *team = NULL;
    egg_t *egg = NULL;

    for (size_t i = 0; i != nb_teams; i++) {
        team = list_get_elem_at_position(serv->teams, i);
        if (team != NULL
            && strncmp(team->name, client->team_name, strlen(team->name)) == 0
            && team_can_add_player(serv, team)) {
            team->nb_player++;
            egg = list_get_elem_at_back(team->eggs);
            list_del_elem_at_back(&team->eggs);
            client->player.x = egg->x;
            client->player.y = egg->y;
            serv->map[egg->x][egg->y].nb_player_on += 1;
            free(egg);
            return (true);
        }
    }
    return (false);
}

bool team_remove_client(server_t *serv, const client_t *client)
{
    size_t nb_teams = list_get_size(serv->teams);
    team_t *team = NULL;

    for (size_t i = 0; i != nb_teams; i++) {
        team = list_get_elem_at_position(serv->teams, i);
        if (team == NULL)
            continue;
        if (strcmp(team->name, client->team_name) == 0) {
            team->nb_player--;
            return (true);
        }
    }
    return (false);
}

int team_get_free_space(team_t *team)
{
    if (team == NULL)
        return (0);
    return list_get_size(team->eggs);
}
