/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_struct
*/

#include <stdlib.h>
#include "server.h"

server_t *init_struct(void)
{
    server_t *tmp = malloc(sizeof(server_t));
    list_t *node = {NULL};

    if (tmp == NULL)
        return tmp;
    tmp->port = -1;
    tmp->resX = -1;
    tmp->resY = -1;
    tmp->tName = NULL;
    tmp->clientNb = -1;
    tmp->freq = 100;
    tmp->client = node;
    tmp->map = NULL;
    return tmp;
}

int get_team_nb(server_t *serv)
{
    int index = 0;

    for (index = 0; serv->tName[index] != NULL;)
        index++;
    return index;
}

void free_struct(server_t *serv)
{
    if (serv == NULL)
        return;
    if (serv->tName != NULL) {
        for (int i = 0; serv->tName[i] != NULL; i++)
            free(serv->tName[i]);
        free(serv->tName);
    }
    if (serv->map != NULL)
        free_map(serv);
    free(serv);
}
