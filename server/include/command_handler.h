/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command_handler
*/

#pragma once

#include "server.h"

struct command_handler_s
{
    char command[32];
    bool (*ptr)(server_t *, client_t *, const char *);
};

bool forward(server_t *, client_t *, const char *cmd);
bool right(server_t *, client_t *, const char *cmd);
bool left(server_t *, client_t *, const char *cmd);
bool look(server_t *, client_t *, const char *cmd);
bool inventory(server_t *, client_t *, const char *cmd);
bool broadcast(server_t *, client_t *, const char *cmd);
bool connect_nbr(server_t *, client_t *, const char *cmd);
bool forked(server_t *, client_t *, const char *cmd);
bool eject(server_t *, client_t *, const char *cmd);
bool forward(server_t *, client_t *, const char *cmd);
bool take_object(server_t *, client_t *, const char *cmd);
bool set_object_down(server_t *, client_t *, const char *cmd);
bool start_incantation(server_t *, client_t *, const char *cmd);

bool gui_map_size(server_t *server, client_t *client, const char **args);
bool gui_tile_content(server_t *server, client_t *client, const char **args);
bool gui_map_content(server_t *server, client_t *client, const char **args);
bool gui_all_name(server_t *server, client_t *client, const char **args);
bool gui_player_position(server_t *server, client_t *client, const char **args);
bool gui_player_level(server_t *server, client_t *client, const char **args);
bool gui_player_inventory(server_t *server, client_t *client, const char **args);
bool gui_get_time_unit(server_t *server, client_t *client, const char **args);
bool gui_set_time_unit(server_t *server, client_t *client, const char **args);



static const struct command_handler_s ai_cmds[] = {
    {"Forward", forward},
    {"Right", right},
    {"Left", left},
    {"Look", look},
    {"Inventory", inventory},
    {"Broadcast", broadcast},
    {"Connect_nbr", connect_nbr},
    {"Fork", forked},
    {"Eject", eject},
    {"Take", take_object},
    {"Set", set_object_down},
    {"Incantation", start_incantation}
};
