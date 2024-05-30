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
    server_t *tmp = calloc(1, sizeof(server_t));

    if (tmp == NULL)
        return tmp;
    tmp->port = -1;
    tmp->resX = -1;
    tmp->resY = -1;
    tmp->tName = NULL;
    tmp->clientNb = -1;
    tmp->freq = 100;
    tmp->client = calloc(1, sizeof(list_t));
    tmp->teams = calloc(1, sizeof(list_t));
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
    list_clear(&serv->client);
    list_clear(&serv->teams);
    if (serv->map != NULL)
        free_map(serv);
    free(serv);
}
