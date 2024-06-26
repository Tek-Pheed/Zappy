/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_look
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "server.h"

static cell_t *get_case(server_t *serv, int x, int y)
{
    x = x < 0 ? serv->resX + x : x;
    y = y < 0 ? serv->resY + y : y;
    return &serv->map[x % serv->resY][y % serv->resX];
}

static cell_t *get_current_case(
    server_t *serv, const client_t *cli, int i, int j)
{
    if (cli->player.orient == NORTH)
        return get_case(serv, cli->player.x + j, cli->player.y - i);
    if (cli->player.orient == EAST)
        return get_case(serv, cli->player.x + i, cli->player.y + j);
    if (cli->player.orient == SOUTH)
        return get_case(serv, cli->player.x - j, cli->player.y + i);
    if (cli->player.orient == WEST)
        return get_case(serv, cli->player.x - i, cli->player.y - j);
    return NULL;
}

static void get_stone_cell_next(const cell_t *cell, char **ptr)
{
    if (cell->stone[PHIRAS] > 0) {
        for (int i = 0; i != cell->stone[PHIRAS]; i++)
            *ptr += sprintf(*ptr, "phiras ");
    }
    if (cell->stone[THYSTAME] > 0) {
        for (int i = 0; i != cell->stone[THYSTAME]; i++)
            *ptr += sprintf(*ptr, "thystame ");
    }
}

static void get_stone_cell(const cell_t *cell, char **ptr)
{
    if (cell->stone[LINEMATE] > 0) {
        for (int i = 0; i != cell->stone[LINEMATE]; i++)
            *ptr += sprintf(*ptr, "linemate ");
    }
    if (cell->stone[DERAUMERE] > 0) {
        for (int i = 0; i != cell->stone[DERAUMERE]; i++)
            *ptr += sprintf(*ptr, "deraumere ");
    }
    if (cell->stone[SIBUR] > 0) {
        for (int i = 0; i != cell->stone[SIBUR]; i++)
            *ptr += sprintf(*ptr, "sibur ");
    }
    if (cell->stone[MENDIANE] > 0) {
        for (int i = 0; i != cell->stone[MENDIANE]; i++)
            *ptr += sprintf(*ptr, "mendiane ");
    }
    get_stone_cell_next(cell, ptr);
}

static char *get_items_on_cell(const cell_t *cell)
{
    char buff[DEFAULT_BUFFER_SIZE * 256];
    char *ptr = buff;

    memset(buff, 0, sizeof(buff));
    if (cell->food > 0) {
        for (int i = 0; i != cell->food; i++)
            ptr += sprintf(ptr, "food ");
    }
    get_stone_cell(cell, &ptr);
    return strdup(buff);
}

static char *create_message(const cell_t *cell)
{
    char buff[BUFFER_MAX_SIZE * 49];
    char *tmp = NULL;
    char *ptr = buff;

    for (int i = 0; i != cell->nb_player_on; i++) {
        ptr += sprintf(ptr, "player ");
    }
    tmp = get_items_on_cell(cell);
    ptr += sprintf(ptr, "%s", tmp);
    free(tmp);
    return strdup(buff);
}

static void add_to_str(server_t *serv, const client_t *cli, char **ptr, int i)
{
    cell_t *cell = NULL;
    char *items;

    for (int j = 0; j < (2 * i) + 1; j++) {
        cell = get_current_case(serv, cli, i, j - i);
        items = create_message(cell);
        if (j == 2 * i && i == cli->player.level)
            *ptr += sprintf(*ptr, "%s", items);
        else
            *ptr += sprintf(*ptr, "%s, ", items);
        free(items);
    }
}

bool ai_look_around(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    char buff[BUFFER_MAX_SIZE * 50];
    char *ptr = buff;

    ptr += sprintf(ptr, "[ ");
    for (int i = 0; i <= cli->player.level; i++)
        add_to_str(serv, cli, &ptr, i);
    ptr += sprintf(ptr, "]\n");
    server_send_data(cli, buff);
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    return true;
}
