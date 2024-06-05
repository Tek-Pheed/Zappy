/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** item_msg
*/

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "server.h"

void event_ressource_drop(
    const server_t *serv, const client_t *client, int r_nb)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(serv, EVENT, client->fd, "ressource drop");
    sprintf(buff, "pdr %d %d\n", client->player.number, r_nb);
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_ressource_collect(
    const server_t *serv, const client_t *client, int r_nb)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(serv, EVENT, client->fd, "ressource collected");
    sprintf(buff, "pgt %d %d\n", client->player.number, r_nb);
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_egg_laying(const server_t *serv, const client_t *client)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(serv, EVENT, client->fd, "egg laying");
    sprintf(buff, "pfk %d\n", client->player.number);
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_egg_laid(const server_t *serv, const client_t *client, int egg_nb,
    const ivect2D_t *pos)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(serv, EVENT, client->fd, "egg laid by player");
    sprintf(buff, "enw %d %d %d %d\n", egg_nb, client->player.number, pos->x,
        pos->y);
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_egg_death(const server_t *serv, const client_t *client, int egg_nb)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(serv, EVENT, client->fd, "egg death");
    sprintf(buff, "edi %d\n", egg_nb);
    server_event_send_many(serv, GRAPHICAL, buff);
}
