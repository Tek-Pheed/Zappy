/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_events
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "client.h"
#include "define.h"
#include "server.h"

void server_event_send_many(
    const server_t *serv, enum client_state client_target, const char *buff)
{
    size_t clients = list_get_size(serv->client);
    client_t *client = NULL;

    for (size_t i = 0; i != clients; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL)
            continue;
        if (client->state != client_target)
            continue;
        server_send_data(client, buff);
    }
}
