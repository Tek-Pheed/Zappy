/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_handler
*/

#pragma once

#include "server.h"

void server_send_data(client_t *client, const char *data);

void handle_login_request(server_t *serv, client_t *client);
