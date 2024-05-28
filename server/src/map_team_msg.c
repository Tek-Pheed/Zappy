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

char *map_size(server_t *serv)
{
    char *buff = calloc(25, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "msz %d %d\n", serv->resX, serv->resY);
    return buff;
}

char *tile_content(server_t *serv, int x, int y)
{
    char *buff = calloc(50, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        serv->map[x][y].food, serv->map[x][y].stone[LINEMATE],
        serv->map[x][y].stone[DERAUMERE], serv->map[x][y].stone[SIBUR],
        serv->map[x][y].stone[MENDIANE], serv->map[x][y].stone[PHIRAS],
        serv->map[x][y].stone[THYSTAME]);
    return buff;
}

char *all_content(server_t *serv)
{
    char *buff = calloc(serv->resX * serv->resY * 50, sizeof(char));

    if (!buff)
        return NULL;
    for (int i = 0; i != serv->resX; i++) {
        for (int j = 0; j != serv->resY; j++)
            strcat(buff, tile_content(serv, i, j));
    }
    return buff;
}

static char *team_name(server_t *serv, int ind)
{
    char *buff = calloc(25, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "tna %s\n", serv->tName[ind]);
    return buff;
}

char *all_name(server_t *serv)
{
    char *buff = calloc(serv->teamNb * 25, sizeof(char));

    if (!buff)
        return NULL;
    for (int i = 0; serv->tName[i] != NULL; i++) {
        strcat(buff, team_name(serv, i));
    }
    return buff;
}
