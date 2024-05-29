/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_handling
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include "server.h"
#include "client_handler.h"

void server_send_data(client_t *client, const char *data)
{
    if (client->write_buffer[0] == '\0') {
        strcpy(client->write_buffer, data);
    } else if (strlen(client->write_buffer) + strlen(client->read_buffer)
        < BUFFER_MAX_SIZE) {
        strcat(client->write_buffer, data);
    }
}

void handle_login_request(UNUSED server_t *serv, client_t *client)
{
    if (client->state == CREATED) {
        strcpy(client->team_name, client->read_buffer);
        if (strcmp(client->read_buffer, "GRAPHIC") == 0) {
            client->state = GRAPHICAL;
        } else {
            client->state = AI;
        }
    }
}

// TODO
void read_client_data(server_t *serv, fd_set *read_set)
{
    client_t *client = NULL;
    list_t *clients = serv->client;
    size_t clients_nb = list_get_size(clients);

    for (size_t i = 0; i != clients_nb; i++) {
        client = list_get_elem_at_position(clients, i);
        if (client == NULL)
            continue;
        if (FD_ISSET(client->fd, read_set)) {
            continue;
        }
    }
}
