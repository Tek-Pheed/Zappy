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
    if (strcmp(to_lower_case(str), "linemate") == 0)
        return 0;
    if (strcmp(to_lower_case(str), "deraumere") == 0)
        return 1;
    if (strcmp(to_lower_case(str), "sibur") == 0)
        return 2;
    if (strcmp(to_lower_case(str), "mendiane") == 0)
        return 3;
    if (strcmp(to_lower_case(str), "phiras") == 0)
        return 4;
    if (strcmp(to_lower_case(str), "thystame") == 0)
        return 5;
    if (strcmp(to_lower_case(str), "food") == 0)
        return 6;
    return -1;
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
            return true;
        }
    }
    server_send_data(cli, "ko\n");
    return false;
}

bool ai_take_object(server_t *serv, client_t *cli, const char *obj)
{
    int id = get_id_from_str(obj);

    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    if (id == 6) {
        if (serv->map[cli->player.x][cli->player.x].food > 0) {
            cli->player.food += 1;
            serv->map[cli->player.x][cli->player.x].food -= 1;
            event_ressource_collect(serv, cli, 0);
            server_send_data(cli, "ok\n");
            event_player_inventory(serv, cli);
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

    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    if (id == 6 && cli->player.food > 0) {
        cli->player.food -= 1;
        serv->map[cli->player.x][cli->player.y].food += 1;
        server_send_data(cli, "ok\n");
        event_player_inventory(serv, cli);
        return true;
    } else if (id != -1 && cli->player.stone[id] > 0) {
        cli->player.stone[id] -= 1;
        serv->map[cli->player.x][cli->player.y].stone[id] += 1;
        server_send_data(cli, "ok\n");
        event_player_inventory(serv, cli);
        return true;
    }
    server_send_data(cli, "ko\n");
    return false;
}
