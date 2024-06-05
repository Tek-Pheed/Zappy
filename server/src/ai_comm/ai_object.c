/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_object
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "commands.h"
#include "server.h"

char *to_lower_case(const char *str)
{
    char *lowerStr = malloc(strlen(str) + 1);

    if (lowerStr == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++)
        lowerStr[i] = tolower((unsigned char) str[i]);
    lowerStr[strlen(str)] = '\0';
    return lowerStr;
}

static int get_id_from_str(const char *str)
{
    char *stone = to_lower_case(str);
    int val = -1;

    if (strcmp(stone, "linemate") == 0)
        val = 0;
    if (strcmp(stone, "deraumere") == 0)
        val = 1;
    if (strcmp(stone, "sibur") == 0)
        val = 2;
    if (strcmp(stone, "mendiane") == 0)
        val = 3;
    if (strcmp(stone, "phiras") == 0)
        val = 4;
    if (strcmp(stone, "thystame") == 0)
        val = 5;
    if (strcmp(stone, "food") == 0)
        val = 6;
    free(stone);
    return val;
}

static bool take_stone(server_t *serv, client_t *cli, int id)
{
    if (id == LINEMATE || id == DERAUMERE || id == SIBUR || id == MENDIANE
        || id == PHIRAS || id == THYSTAME) {
        if (serv->map[cli->player.x][cli->player.y].stone[id] > 0) {
            cli->player.stone[id] += 1;
            serv->map[cli->player.x][cli->player.y].stone[id] -= 1;
            event_ressource_collect(serv, cli, id + 1);
            server_send_data(cli, "ok\n");
            event_player_inventory(serv, cli);
            event_tile_update(serv, cli->player.x, cli->player.y);
            return true;
        }
    }
    server_send_data(cli, "ko\n");
    return false;
}

static void set_duration(client_t *cli)
{
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
}

bool ai_take_object(server_t *serv, client_t *cli, const char *obj)
{
    int id = get_id_from_str(obj);

    set_duration(cli);
    if (id == 6) {
        if (serv->map[cli->player.x][cli->player.y].food > 0) {
            cli->player.food += 1;
            serv->map[cli->player.x][cli->player.y].food -= 1;
            event_ressource_collect(serv, cli, 0);
            server_send_data(cli, "ok\n");
            event_player_inventory(serv, cli);
            event_tile_update(serv, cli->player.x, cli->player.y);
            return true;
        } else {
            server_send_data(cli, "ko\n");
            return false;
        }
    } else {
        return take_stone(serv, cli, id);
    }
    return true;
}

bool ai_set_object(server_t *serv, client_t *cli, const char *obj)
{
    int id = get_id_from_str(obj);

    set_duration(cli);
    if (id == 6 && cli->player.food > 0) {
        cli->player.food -= 1;
        serv->map[cli->player.x][cli->player.y].food += 1;
        server_send_data(cli, "ok\n");
        event_player_inventory(serv, cli);
        event_tile_update(serv, cli->player.x, cli->player.y);
        return true;
    } else if (id != -1 && cli->player.stone[id] > 0) {
        cli->player.stone[id] -= 1;
        serv->map[cli->player.x][cli->player.y].stone[id] += 1;
        server_send_data(cli, "ok\n");
        event_player_inventory(serv, cli);
        event_tile_update(serv, cli->player.x, cli->player.y);
        return true;
    }
    server_send_data(cli, "ko\n");
    return false;
}
