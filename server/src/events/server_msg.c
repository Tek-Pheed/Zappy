/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "commands.h"
#include "define.h"
#include "server.h"

void event_end_game(const server_t *serv, const char *winner)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(EVENT, 0, "end game");
    sprintf(buff, "seg %s\n", winner);
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_server_message(server_t *serv, const char *msg)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(EVENT, 0, "server message");
    sprintf(buff, "smg %s\n", msg);
    server_event_send_many(serv, GRAPHICAL, buff);
}

void event_unknow_command(client_t *client)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(EVENT, client->fd, "unknown command");
    if (client->state == GRAPHICAL)
        sprintf(buff, "suc\n");
    else
        strcpy(buff, "ko\n");
    server_send_data(client, buff);
}

void event_command_parameter(client_t *client)
{
    char buff[DEFAULT_BUFFER_SIZE];

    memset(buff, 0, sizeof(buff));
    server_log(EVENT, client->fd, "wrong command parameters");
    if (client->state == GRAPHICAL)
        sprintf(buff, "sbp\n");
    else
        strcpy(buff, "ko\n");
    server_send_data(client, buff);
}
