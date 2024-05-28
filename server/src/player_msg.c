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
