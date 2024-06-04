/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_event_msg
*/

#include <stdio.h>
#include <string.h>
#include "client.h"
#include "commands.h"
#include "server.h"

void event_expulsion(server_t *serv, client_t *client)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(EVENT, client->fd, "expulsion");
    sprintf(buff, "pex #%d\n", client->player.number);
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_broadcast(server_t *serv, client_t *client, char *msg)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(EVENT, client->fd, "broadcast");
    sprintf(buff, "pbc #%d %s\n", client->player.number, msg);
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_end_incantation(
    server_t *serv, client_t *client, const ivect2D_t *pos, const char *result)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(EVENT, client->fd, "end incantation");
    sprintf(buff, "pie %d %d %s\n", pos->x, pos->y, result);
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_player_death(server_t *serv, client_t *client)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(EVENT, client->fd, "player dead");
    sprintf(buff, "pdi #%d\n", client->player.number);
    server_send_data(client, "dead\n");
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_player_connection_egg(server_t *serv, client_t *client)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(EVENT, client->fd, "player connection on an egg");
    sprintf(buff, "ebo #%d\n", client->player.number);
    server_event_send_many(serv, GRAPHICAL, buff);
}
