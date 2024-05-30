/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_elevation
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static const int s_required[7][6] = {{1, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 0},
    {2, 0, 1, 0, 2, 0}, {1, 1, 2, 0, 1, 0}, {1, 2, 1, 3, 0, 0},
    {1, 2, 3, 0, 1, 0}, {2, 2, 2, 2, 2, 1}};
static const int p_required[7] = {1, 2, 2, 4, 4, 6, 6};

static bool check_nb_players(server_t *serv, client_t *cli)
{
    int client_len = 0;
    client_t *tmp;

    if (serv->map[cli->player.x][cli->player.y].nb_player_on
        < p_required[cli->player.level - 1])
        return false;
    client_len = list_get_size(serv->client);
    for (int i = 0; i != client_len; i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp->player.level != cli->player.level)
            return false;
    }
    return true;
}

static bool check_stone(server_t *serv, client_t *cli)
{
    for (int i = 0; i != 6; i++) {
        if (serv->map[cli->player.x][cli->player.y].stone[i]
            != s_required[cli->player.level - 1][i])
            return false;
    }
    return true;
}

bool ai_elevation(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    char msg[BUFFER_MAX_SIZE];

    memset(msg, '\0', sizeof(msg));
    if (check_stone(serv, cli) && check_nb_players(serv, cli)) {
        sprintf(msg, "Elevation underway\n");
        server_send_data(cli, msg);
    }
    cli->cmd_duration = 300;
    gettimeofday(&cli->last_cmd_time, NULL);
    return true;
}
