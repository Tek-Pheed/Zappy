/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#include "server.h"
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

static int is_on(int val)
{
    static int i = 1;

    if (val == 1)
        i = 0;
    return i;
}

static void stop_server(UNUSED int signal)
{
    is_on(1);
}

static int init_server_socket(int port)
{
    int res = 0;
    int sock_fd = 0;
    struct sockaddr_in sock_settings = {.sin_family = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port = htons(port)};

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd == -1)
        return (-1);
    res = bind(
        sock_fd, (struct sockaddr *) &sock_settings, sizeof(sock_settings));
    if (res == -1) {
        close(sock_fd);
        return (-1);
    }
    return (sock_fd);
}

static bool start_socket(int fd)
{
    if (listen(fd, FD_SETSIZE) == -1) {
        close(fd);
        return (false);
    }
    return (true);
}

bool init_server(server_t *serv)
{
    serv->socket = init_server_socket(serv->port);
    if (serv->socket == -1) {
        return false;
    }
    if (!start_socket(serv->socket))
        return false;
    return true;
}

int run_server(server_t *serv)
{
    if (!init_server(serv)) {
        perror("Unable to initialize server");
        return 84;
    }
    signal(SIGINT, stop_server);
    while (is_on(0))
        server_loop(serv);
    return 0;
}
