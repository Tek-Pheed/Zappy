/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** networking
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include "list.h"
#include "server.h"

void handle_destroyed_clients(server_t *server)
{
    client_t *client = NULL;
    size_t clients = list_get_size(server->client);
    int to_remove[clients];
    size_t index = 0;

    memset(to_remove, -1, clients);
    for (size_t i = 0; i != clients; i++) {
        client = list_get_elem_at_position(server->client, i);
        if (client != NULL && client->fd == -1) {
            to_remove[index] = (int) i;
            index++;
        }
    }
    for (size_t i = 0; i != clients && to_remove[i] != -1; i++)
        list_del_elem_at_position(&server->client, to_remove[i]);
}

static void disable_client(
    const server_t *serv, client_t *client, int write_ret)
{
    if (write_ret == -1) {
        server_log(serv, EVENT, client->fd, "client disconnected");
        close(client->fd);
        client->fd = -1;
    }
}

void send_buffered_data(server_t *server, fd_set *write_fds)
{
    int write_ret;
    client_t *client = NULL;
    size_t size = list_get_size(server->client);

    for (size_t i = 0; i != size; i++) {
        client = list_get_elem_at_position(server->client, i);
        write_ret = 0;
        if (client == NULL || client->write_buffer[0] == '\0')
            continue;
        if (FD_ISSET(client->fd, write_fds)) {
            write_ret = write(client->fd, client->write_buffer,
                strlen(client->write_buffer));
            server_log(server, SENDING, client->fd, client->write_buffer);
        }
        disable_client(server, client, write_ret);
        memset(client->write_buffer, '\0', sizeof(client->write_buffer));
    }
}
