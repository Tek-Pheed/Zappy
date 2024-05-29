/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "server.h"

char *conn_new_player(server_t *serv)
{
    char *buff = calloc(25, sizeof(char));
    client_t *cl;

    if (!buff)
        return NULL;
    cl = list_get_elem_at_back(serv->client);
    sprintf(buff, "pnw #%d %d %d %d %d %s\n", cl->number, cl->posX, cl->posY,
        cl->orient, cl->level, cl->team);
    return buff;
}

char *player_position(server_t *serv, int p_index)
{
    client_t *tmp = NULL;
    char *buff = calloc(25, sizeof(char));

    if (list_is_empty(serv->client))
        return NULL;
    for (int i = 0; i != list_get_size(serv->client); i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp == NULL)
            continue;
        if (tmp->number == p_index) {
            sprintf(buff, "ppo #%d %d %d %d\n", p_index, tmp->posX, tmp->posY,
                tmp->orient);
            return buff;
        }
        buff = NULL;
    }
    return buff;
}

char *player_level(server_t *serv, int p_index)
{
    client_t *tmp = NULL;
    char *buff = calloc(25, sizeof(char));

    if (list_is_empty(serv->client))
        return NULL;
    for (int i = 0; i != list_get_size(serv->client); i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp == NULL)
            continue;
        if (tmp->number == p_index) {
            sprintf(buff, "plv #%d %d\n", p_index, tmp->level);
            return buff;
        }
        buff = NULL;
    }
    return buff;
}

char *player_inventory(server_t *serv, int p_index)
{
    client_t *tmp = NULL;
    char *buff = calloc(25, sizeof(char));

    if (list_is_empty(serv->client))
        return NULL;
    for (int i = 0; i != list_get_size(serv->client); i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp == NULL)
            continue;
        if (tmp->number == p_index) {
            sprintf(buff, "pin #%d %d %d %d %d %d %d %d %d %d\n", p_index,
                tmp->posX, tmp->posY, tmp->food, tmp->stone[LINEMATE],
                tmp->stone[DERAUMERE], tmp->stone[SIBUR], tmp->stone[MENDIANE],
                tmp->stone[PHIRAS], tmp->stone[THYSTAME]);
            return buff;
        }
        buff = NULL;
    }
    return buff;
}
