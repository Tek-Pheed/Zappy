/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_handler
*/

#pragma once

#include "server.h"

void server_send_data(client_t *client, const char *data);

bool handle_login_request(client_t *client, const char *cmd);
bool run_command(server_t *serv, client_t *client, const char *cmd);
