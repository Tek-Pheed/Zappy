/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** logger
*/

#include <stdio.h>
#include "server.h"

static int logger_case(enum log_level level, int client_fd, const char *data)
{
    switch (level) {
        case EVENT:
            printf("[EVENT] %s", data);
            if (client_fd >= 1)
                return (printf(" on socket %d\n", client_fd));
            else
                return (printf("\n"));
        case RECEIVING:
            return (printf("[RECEIVED] from socket %d: %s", client_fd, data));
        case SENDING:
            return (printf("[SENDING] to socket %d: %s", client_fd, data));
        case WARNING:
            return (printf("[WARNING]: %s\n", data));
        case PROCESS:
            return (printf("[PROCESS] command %s\n", data));
        default:
            break;
    }
    return -1;
}

int server_log(const server_t *serv, enum log_level level, int client_fd,
    const char *data)
{
    if (serv->verbose == false)
        return 0;
    if (logger_case(level, client_fd, data) == -1)
        return (printf("[INFO]: %s\n", data));
    return 0;
}
