/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "server.h"

char *event_conn_new_player(server_t *serv)
{
    char *buff = calloc(BUFFER_MAX_SIZE * 2, sizeof(char));
    client_t *cl;

    if (!buff)
        return NULL;
    cl = list_get_elem_at_back(serv->client);
    if (cl == NULL || cl->state != AI) {
        free(buff);
        return NULL;
    }
    sprintf(buff, "pnw #%d %d %d %d %d %s\n", cl->player.number, cl->player.x,
        cl->player.y, cl->player.orient, cl->player.level,
        cl->player.team_name);
    return buff;
}

char *player_position(server_t *serv, int p_index)
{
    client_t *tmp = NULL;
    char *buff = calloc(BUFFER_MAX_SIZE * 2, sizeof(char));

    if (list_is_empty(serv->client)) {
        free(buff);
        return NULL;
    }
    for (size_t i = 0; i != list_get_size(serv->client); i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp == NULL || tmp->state != AI)
            continue;
        if (tmp->player.number == p_index) {
            sprintf(buff, "ppo #%d %d %d %d\n", p_index, tmp->player.x,
                tmp->player.y, tmp->player.orient);
            return buff;
        }
    }
    free(buff);
    return NULL;
}

char *player_level(server_t *serv, int p_index)
{
    client_t *tmp = NULL;
    char *buff = calloc(BUFFER_MAX_SIZE * 2, sizeof(char));

    if (list_is_empty(serv->client)) {
        free(buff);
        return NULL;
    }
    for (size_t i = 0; i != list_get_size(serv->client); i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp == NULL || tmp->state != AI)
            continue;
        if (tmp->player.number == p_index) {
            sprintf(buff, "plv #%d %d\n", p_index, tmp->player.level);
            return buff;
        }
        buff = NULL;
    }
    return buff;
}

char *player_inventory(server_t *serv, int p_index)
{
    client_t *tmp = NULL;
    char *buff = calloc(BUFFER_MAX_SIZE * 2, sizeof(char));

    if (list_is_empty(serv->client)) {
        free(buff);
        return NULL;
    }
    for (size_t i = 0; i != list_get_size(serv->client); i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp == NULL || tmp->state != AI)
            continue;
        if (tmp->player.number == p_index) {
            sprintf(buff, "pin #%d %d %d %d %d %d %d %d %d %d\n", p_index,
                tmp->player.x, tmp->player.y, tmp->player.food,
                tmp->player.stone[LINEMATE], tmp->player.stone[DERAUMERE],
                tmp->player.stone[SIBUR], tmp->player.stone[MENDIANE],
                tmp->player.stone[PHIRAS], tmp->player.stone[THYSTAME]);
        }
    }
    return buff;
}

char *event_start_incantation(player_t *player, int *p_nb, int size)
{
    char *buff = calloc(BUFFER_MAX_SIZE, sizeof(char));
    char str[BUFFER_MAX_SIZE];

    if (!buff)
        return NULL;
    sprintf(buff, "pic %d %d %d #%d", player->x, player->y, player->level,
        player->number);
    for (int i = 0; p_nb[i] != -1 && i != size; i++) {
        sprintf(str, " #%d", p_nb[i]);
        strcat(buff, str);
    }
    strcat(buff, "\n");
    return buff;
}