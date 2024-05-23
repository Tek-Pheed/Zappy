/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** loop_server
*/

#include <netinet/ip.h>
#include <stdbool.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include "server.h"

static void zero_fds(fd_set *a, fd_set *b)
{
    FD_ZERO(a);
    FD_ZERO(b);
}

int server_loop(server_t *serv)
{
    struct timeval time = {0, CONN_TIMEOUT_DELAY_US};
    fd_set fdset;
    fd_set fdwset;

    zero_fds(&fdset, &fdwset);
    FD_SET(serv->socket, &fdset);
    if (select(FD_SETSIZE, &fdset, &fdwset, NULL, &time) != -1) {
        if (FD_ISSET(serv->socket, &fdset) != 0)
            // new connection
            return 0;
        // command
        return 0;
    }
    return 0;
}
