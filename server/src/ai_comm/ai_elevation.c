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
    int count = 0;
    client_t *tmp;

    if (serv->map[cli->player.x][cli->player.y].nb_player_on
        < p_required[cli->player.level - 1])
        return false;
    client_len = list_get_size(serv->client);
    for (int i = 0; i != client_len; i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp->player.x == cli->player.x && tmp->player.y == cli->player.y
            && tmp->player.level == cli->player.level)
            count++;
    }
    if (count < p_required[cli->player.level - 1])
        return false;
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

static void level_up_all(server_t *serv, UNUSED client_t *cli)
{
    int client_len = 0;
    client_t *tmp;

    client_len = list_get_size(serv->client);
    for (int i = 0; i != client_len; i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp->player.elevating == true) {
            tmp->player.level += 1;
            tmp->player.elevating = false;
        }
    }
}

static void remove_stone_used(server_t *serv, client_t *cli)
{
    for (int i = 0; i != 6; i++) {
        serv->map[cli->player.x][cli->player.y].stone[i] -=
            s_required[cli->player.level - 1][i];
    }
}

static void mark_player_elevating(server_t *serv, client_t *cli)
{
    int count = 0;
    int client_len = 0;
    client_t *tmp;

    client_len = list_get_size(serv->client);
    for (int i = 0;
        i != client_len && count >= p_required[cli->player.level - 1]; i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp->player.x == cli->player.x && tmp->player.y == cli->player.y
            && tmp->player.level == cli->player.level) {
            count++;
            tmp->player.elevating = true;
            tmp->cmd_duration = 300;
            gettimeofday(&tmp->last_cmd_time, NULL);
        }
    }
}

bool ai_elevation(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    bool val;

    if (check_stone(serv, cli) && check_nb_players(serv, cli)) {
        mark_player_elevating(serv, cli);
        server_send_data(cli, "Elevation underway\n");
        val = true;
        check_lvl_player(serv);
    } else {
        server_send_data(cli, "ko\n");
        val = false;
    }
    cli->cmd_duration = 300;
    gettimeofday(&cli->last_cmd_time, NULL);
    list_add_elem_at_position(&cli->cmds, strdup("EndIncantationServer\n"), 2);
    return val;
}

bool ai_end_elevation(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    char msg[BUFFER_MAX_SIZE];
    bool val;

    memset(msg, '\0', sizeof(msg));
    if (check_stone(serv, cli) && check_nb_players(serv, cli)) {
        remove_stone_used(serv, cli);
        level_up_all(serv, cli);
        sprintf(msg, "Current level: %d\n", cli->player.level);
        server_send_data(cli, msg);
        val = true;
    } else {
        server_send_data(cli, "ko\n");
        val = false;
    }
    cli->cmd_duration = 300;
    gettimeofday(&cli->last_cmd_time, NULL);
    return val;
}
