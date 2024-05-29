/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** networking
*/

#pragma once
#include <sys/select.h>
#include "server.h"

// Remove clients in bad state
void handle_destroyed_clients(server_t *server);

// Send buffered data to client
void send_buffered_data(server_t *server, fd_set *write_fds);

// Handle client requests
void read_client_data(server_t *serv, fd_set *read_set);
