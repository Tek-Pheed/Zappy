/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** logger
*/

#include <stdio.h>
#include "server.h"

int server_log(enum log_level level, int client_fd, const char *data)
{
    switch (level) {
        case EVENT:
            return (printf("[EVENT] %s on client %d\n", data, client_fd));
        case RECEIVING:
            return (printf("[RECEIVED] from client %d: %s\n",
                client_fd, data));
        case SENDING:
            return (printf("[SENDING] to client %d: %s\n", client_fd, data));
        case WARNING:
            return (printf("[WARNING]: %s\n", data));
        case PROCESS:
            return (printf("[PROCESS] command %s\n", data));
        default:
            break;
    }
    return (printf("[INFO]: %s\n", data));
}
