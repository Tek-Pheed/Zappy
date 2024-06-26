/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_elevation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "server.h"

static const int s_required[7][6] = {{1, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 0},
    {2, 0, 1, 0, 2, 0}, {1, 1, 2, 0, 1, 0}, {1, 2, 1, 3, 0, 0},
    {1, 2, 3, 0, 1, 0}, {2, 2, 2, 2, 2, 1}};
static const int p_required[7] = {1, 2, 2, 4, 4, 6, 6};

static bool check_nb_players(server_t *serv, const client_t *cli)
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
        if (tmp == NULL)
            continue;
        if (tmp->state == AI && tmp->player.x == cli->player.x
            && tmp->player.y == cli->player.y
            && tmp->player.level == cli->player.level)
            count++;
    }
    if (count < p_required[cli->player.level - 1])
        return false;
    return true;
}

static bool check_stone(const server_t *serv, const client_t *cli)
{
    for (int i = 0; i != 6; i++) {
        if (serv->map[cli->player.x][cli->player.y].stone[i]
            < s_required[cli->player.level - 1][i])
            return false;
    }
    return true;
}

static void level_up_all(server_t *serv, UNUSED client_t *cli)
{
    char msg[BUFFER_MAX_SIZE];
    int client_len = 0;
    client_t *tmp;

    client_len = list_get_size(serv->client);
    for (int i = 0; i != client_len; i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp == NULL)
            continue;
        if (tmp->state == AI && tmp->player.elevating == cli->player.number) {
            tmp->player.level += 1;
            tmp->player.elevating = -1;
            sprintf(msg, "Current level: %d\n", tmp->player.level);
            server_send_data(tmp, msg);
            event_player_level(serv, tmp);
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

static int mark_player_elevating(server_t *serv, client_t *cli)
{
    int count = 1;
    int client_len = 0;
    client_t *tmp;

    cli->player.elevating = cli->player.number;
    client_len = list_get_size(serv->client);
    for (int i = 0;
        i != client_len && count <= p_required[cli->player.level - 1]; i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp != NULL && tmp->state == AI && tmp->player.x == cli->player.x
            && tmp->player.y == cli->player.y
            && tmp->player.level == cli->player.level) {
            count++;
            tmp->player.elevating = cli->player.number;
            tmp->cmd_duration = 300;
            gettimeofday(&tmp->last_cmd_time, NULL);
        }
    }
    return (count);
}

static int *getelevated(server_t *serv, int size)
{
    int *elevated = calloc(size + 1, sizeof(int));
    size_t ls = list_get_size(serv->client);
    client_t *cli = NULL;
    size_t y = 0;

    for (size_t i = 0; i < ls; i++) {
        if (i >= (size_t) size)
            break;
        cli = list_get_elem_at_position(serv->client, i);
        if (cli == NULL || cli->state != AI)
            continue;
        elevated[y] = cli->player.number;
        y++;
    }
    elevated[y] = -1;
    return (elevated);
}

bool ai_elevation(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    bool val;
    int n = 0;
    int *elevated = NULL;

    if (check_stone(serv, cli) && check_nb_players(serv, cli)) {
        n = mark_player_elevating(serv, cli);
        server_send_data(cli, "Elevation underway\n");
        val = true;
        elevated = getelevated(serv, n);
        event_start_incantation(serv, cli, elevated, n);
        free(elevated);
        list_add_elem_at_back(&cli->cmds, strdup("EndIncantationServer\n"));
    } else {
        server_send_data(cli, "ko\n");
        val = false;
    }
    cli->cmd_duration = 300;
    gettimeofday(&cli->last_cmd_time, NULL);
    return val;
}

static void fail_elevation(server_t *serv, client_t *cli)
{
    int len = list_get_size(serv->client);
    client_t *tmp;

    for (int i = 0; i != len; i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp == NULL || tmp->state == GRAPHICAL)
            continue;
        if (tmp->player.elevating == cli->player.number) {
            tmp->player.elevating = -1;
            server_send_data(tmp, "ko\n");
        }
    }
}

bool ai_end_elevation(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    char msg[BUFFER_MAX_SIZE];
    bool val;

    memset(msg, '\0', sizeof(msg));
    if (check_stone(serv, cli) && check_nb_players(serv, cli)) {
        remove_stone_used(serv, cli);
        level_up_all(serv, cli);
        event_end_incantation(
            serv, cli, &((ivect2D_t){cli->player.x, cli->player.y}), "ok");
        val = true;
    } else {
        fail_elevation(serv, cli);
        val = false;
        event_end_incantation(
            serv, cli, &((ivect2D_t){cli->player.x, cli->player.y}), "ko");
    }
    check_lvl_player(serv);
    return val;
}
