/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** gui_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

char *map_size(const server_t *serv)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "msz %d %d\n", serv->resX, serv->resY);
    return buff;
}

char *tile_content(const server_t *serv, int x, int y)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE * 2, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        serv->map[x][y].food, serv->map[x][y].stone[LINEMATE],
        serv->map[x][y].stone[DERAUMERE], serv->map[x][y].stone[SIBUR],
        serv->map[x][y].stone[MENDIANE], serv->map[x][y].stone[PHIRAS],
        serv->map[x][y].stone[THYSTAME]);
    return buff;
}

char *all_content(const server_t *serv)
{
    char *tmp = NULL;
    char *buff = calloc(serv->resX * serv->resY * 50, sizeof(char));

    if (!buff)
        return NULL;
    for (int i = 0; i != serv->resX; i++) {
        for (int j = 0; j != serv->resY; j++) {
            tmp = tile_content(serv, i, j);
            strcat(buff, tmp);
            free(tmp);
        }
    }
    return buff;
}

static char *team_name(team_t *team)
{
    char *buff = calloc(strlen(team->name) + 7, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "tna %s\n", team->name);
    return buff;
}

char *all_name(const server_t *serv)
{
    int len_team = list_get_size(serv->teams);
    char *buff = calloc(len_team * DEFAULT_BUFFER_SIZE, sizeof(char));
    char *team = NULL;
    team_t *tmp;

    if (!buff)
        return NULL;
    for (int i = 0; i != len_team; i++) {
        tmp = list_get_elem_at_position(serv->teams, i);
        if (tmp == NULL)
            continue;
        team = team_name(tmp);
        strcat(buff, team);
        free(team);
    }
    return buff;
}
