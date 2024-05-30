/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command_handler
*/

#pragma once

#include <stddef.h>
#include "server.h"

struct command_handler_s {
    char command[32];
    size_t nb_args;
    union ptr_u {
        bool (*ai_ptr)(server_t *, client_t *, const char *);
        bool (*gui_ptr)(server_t *, client_t *, char **);
    } ptr;
};

// bool ai_forward(server_t *, client_t *, const char *cmd);
// bool ai_right(server_t *, client_t *, const char *cmd);
// bool ai_left(server_t *, client_t *, const char *cmd);
// bool ai_look(server_t *, client_t *, const char *cmd);
// bool ai_inventory(server_t *, client_t *, const char *cmd);
// bool ai_broadcast(server_t *, client_t *, const char *cmd);
// bool ai_connect_nbr(server_t *, client_t *, const char *cmd);
// bool ai_forked(server_t *, client_t *, const char *cmd);
// bool ai_eject(server_t *, client_t *, const char *cmd);
// bool ai_forward(server_t *, client_t *, const char *cmd);
// bool ai_take_object(server_t *, client_t *, const char *cmd);
// bool ai_set_object_down(server_t *, client_t *, const char *cmd);
// bool ai_start_incantation(server_t *, client_t *, const char *cmd);

bool gui_map_size(server_t *server, client_t *client, UNUSED char **args);
bool gui_tile_content(server_t *server, client_t *client, UNUSED char **args);
bool gui_map_content(server_t *server, client_t *client, char **args);
bool gui_all_name(server_t *server, client_t *client, UNUSED char **args);
bool gui_player_position(server_t *server, client_t *client, char **args);
bool gui_player_level(server_t *server, client_t *client, char **args);
bool gui_player_inventory(server_t *server, client_t *client, char **args);
bool gui_get_time_unit(server_t *server, client_t *client, char **args);
bool gui_set_time_unit(server_t *server, client_t *client, char **args);

// static const struct command_handler_s ai_cmds[] = {
//     {.command = "Forward", .nb_args = 0, .ptr = {.ai_ptr = ai_forward}},
//     {.command = "Right", .nb_args = 0, .ptr = {.ai_ptr = ai_right}},
//     {.command = "Left", .nb_args = 0, .ptr = {.ai_ptr = ai_left}},
//     {.command = "Look", .nb_args = 0, .ptr = {.ai_ptr = ai_look}},
//     {.command = "Inventory", .nb_args = 0, .ptr = {.ai_ptr = ai_inventory}},
//     {.command = "Broadcast", .nb_args = 1, .ptr = {.ai_ptr = ai_broadcast}},
//     {.command = "Connect_nbr",
//         .nb_args = 0,
//         .ptr = {.ai_ptr = ai_connect_nbr}},
//     {.command = "Fork", .nb_args = 0, .ptr = {.ai_ptr = ai_forked}},
//     {.command = "Eject", .nb_args = 0, .ptr = {.ai_ptr = ai_eject}},
//     {.command = "Take", .nb_args = 1, .ptr = {.ai_ptr = ai_take_object}},
//     {.command = "Set", .nb_args = 1, .ptr = {.ai_ptr = ai_set_object_down}},
//     {.command = "Incantation",
//         .nb_args = 0,
//         .ptr = {.ai_ptr = ai_start_incantation}}};

static const struct command_handler_s gui_cmds[] = {
    {.command = "msz", .nb_args = 0, .ptr = {.gui_ptr = gui_map_size}},
    {.command = "bct", .nb_args = 2, .ptr = {.gui_ptr = gui_tile_content}},
    {.command = "mct", .nb_args = 0, .ptr = {.gui_ptr = gui_map_content}},
    {.command = "tna", .nb_args = 0, .ptr = {.gui_ptr = gui_all_name}},
    {.command = "ppo",
        .nb_args = 1,
        .ptr = {.gui_ptr = gui_player_position}},
    {.command = "plv",
        .nb_args = 1,
        .ptr = {.gui_ptr = gui_player_level}},
    {.command = "pin",
        .nb_args = 1,
        .ptr = {.gui_ptr = gui_player_inventory}},
    {.command = "sgt", .nb_args = 0, .ptr = {.gui_ptr = gui_get_time_unit}},
    {.command = "sst", .nb_args = 1, .ptr = {.gui_ptr = gui_set_time_unit}}};
