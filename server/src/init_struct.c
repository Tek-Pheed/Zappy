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
    list_t *node = {NULL, NULL};

    if (tmp == NULL)
        return tmp;
    tmp->_port = -1;
    tmp->_resX = -1;
    tmp->_resY = -1;
    tmp->_tName = NULL;
    tmp->_clientNb = -1;
    tmp->_freq = 100;
    tmp->client = node;
    return tmp;
}

void free_struct(server_t *serv)
{
    if (serv != NULL && serv->_tName != NULL) {
        for (int i = 0; serv->_tName[i] != NULL; i++)
            free(serv->_tName[i]);
        free(serv->_tName);
    }
    if (serv != NULL)
        free(serv);
}
