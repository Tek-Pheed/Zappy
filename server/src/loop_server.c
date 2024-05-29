/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** loop_server
*/

#include <netinet/ip.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include "list.h"
#include "networking.h"
#include "server.h"

static void zero_fds(fd_set *a, fd_set *b)
{
    FD_ZERO(a);
    FD_ZERO(b);
}

static bool add_client(server_t *serv)
{
    struct sockaddr_in clientAddr;
    socklen_t clientSockLen = sizeof(clientAddr);
    client_t *user = calloc(1, sizeof(client_t));
    static int player_index = 0;

    if (user == NULL)
        return false;
    user->fd =
        accept(serv->socket, (struct sockaddr *) &clientAddr, &clientSockLen);
    if (user->fd == -1) {
        free(user);
        return false;
    }
    user->player = calloc(1, sizeof(player_t));
    user->player->number = player_index;
    player_index++;
    list_add_elem_at_back(&serv->client, user);
    strcpy(user->write_buffer, "WELCOME\n");
    user->state = CREATED;
    return (true);
}

static void set_fd(server_t *serv, fd_set *rfds, fd_set *wfds)
{
    client_t *client;
    size_t list_size = list_get_size(serv->client);

    zero_fds(rfds, wfds);
    for (size_t i = 0; i != list_size; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL || client->fd < 1)
            continue;
        FD_SET(client->fd, rfds);
        if (client->write_buffer[0] != '\0')
            FD_SET(client->fd, wfds);
    }
    FD_SET(serv->socket, rfds);
}

int server_loop(server_t *serv)
{
    struct timeval time = {0, CONN_TIMEOUT_DELAY_US};
    fd_set fdset;
    fd_set fdwset;

    set_fd(serv, &fdset, &fdwset);
    if (select(FD_SETSIZE, &fdset, &fdwset, NULL, &time) != -1) {
        send_buffered_data(serv, &fdwset);
        if (FD_ISSET(serv->socket, &fdset) != 0)
            add_client(serv);
        read_client_data(serv, &fdset);
    }
    return 0;
}
