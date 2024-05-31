/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command_handler
*/

#pragma once

#include <stddef.h>
#include "server.h"
#include "ai_comm.h"

struct command_handler_s {
    char command[32];
    size_t nb_args;
    union ptr_u {
        bool (*ai_ptr)(server_t *, client_t *, const char *);
        bool (*gui_ptr)(server_t *, client_t *, char **);
    } ptr;
};

char *tile_content(server_t *serv, int x, int y);
char *all_content(server_t *serv);
char *all_name(server_t *serv);
char *player_position(server_t *serv, int p_index);
char *player_level(server_t *serv, int p_index);
char *player_inventory(server_t *serv, int p_index);
char *conn_new_player(server_t *serv);

char *time_unit_request(server_t *serv);
char *time_unit_modif(server_t *serv, int freq);
char *ressource_drop(int p_index, int r_nb);
char *ressource_collect(int p_index, int r_nb);
char *egg_laying(int p_index);
char *egg_laid(int egg_nb, int p_index, int x, int y);
char *egg_death(int egg_nb);
char *expulsion(int p_index);
char *broadcast(int p_index, char *msg);
char *end_incantation(int x, int y, char *result);
char *player_death(int p_index);
char *player_connection_egg(int p_index);
char *end_game(char *winner);
char *server_message(char *msg);
char *unknow_command(void);
char *command_parameter(void);
char *start_incantation(player_t *player, int *p_nb, int size);

bool gui_map_size(server_t *server, client_t *client, UNUSED char **args);
bool gui_tile_content(server_t *server, client_t *client, UNUSED char **args);
bool gui_map_content(server_t *server, client_t *client, char **args);
bool gui_all_name(server_t *server, client_t *client, UNUSED char **args);
bool gui_player_position(server_t *server, client_t *client, char **args);
bool gui_player_level(server_t *server, client_t *client, char **args);
bool gui_player_inventory(server_t *server, client_t *client, char **args);
bool gui_get_time_unit(server_t *server, client_t *client, char **args);
bool gui_set_time_unit(server_t *server, client_t *client, char **args);

void run_client_commands(server_t *serv);

static const struct command_handler_s ai_cmds[] = {
    {.command = "Forward", .nb_args = 0, .ptr = {.ai_ptr = ai_move_forward}},
    {.command = "Right", .nb_args = 0, .ptr = {.ai_ptr = ai_turn_right}},
    {.command = "Left", .nb_args = 0, .ptr = {.ai_ptr = ai_turn_left}},
    {.command = "Inventory", .nb_args = 0, .ptr = {.ai_ptr = ai_inventory}},
    {.command = "Connect_nbr",
        .nb_args = 0,
        .ptr = {.ai_ptr = ai_connect_nbr}},
    {.command = "Fork", .nb_args = 0, .ptr = {.ai_ptr = ai_fork}},
    {.command = "Eject", .nb_args = 0, .ptr = {.ai_ptr = ai_eject}},
    {.command = "Take", .nb_args = 1, .ptr = {.ai_ptr = ai_take_object}},
    {.command = "Set", .nb_args = 1, .ptr = {.ai_ptr = ai_set_object}},
};
//{.command = "Look", .nb_args = 0, .ptr = {.ai_ptr = ai_look}},
//{.command = "Broadcast", .nb_args = 1, .ptr = {.ai_ptr = ai_broadcast}},
//{.command = "Incantation",
//    .nb_args = 0,
//    .ptr = {.ai_ptr = ai_start_incantation}}

static const struct command_handler_s gui_cmds[] = {
    {.command = "msz", .nb_args = 0, .ptr = {.gui_ptr = gui_map_size}},
    {.command = "bct", .nb_args = 2, .ptr = {.gui_ptr = gui_tile_content}},
    {.command = "mct", .nb_args = 0, .ptr = {.gui_ptr = gui_map_content}},
    {.command = "tna", .nb_args = 0, .ptr = {.gui_ptr = gui_all_name}},
    {.command = "ppo", .nb_args = 1, .ptr = {.gui_ptr = gui_player_position}},
    {.command = "plv", .nb_args = 1, .ptr = {.gui_ptr = gui_player_level}},
    {.command = "pin", .nb_args = 1, .ptr = {.gui_ptr = gui_player_inventory}},
    {.command = "sgt", .nb_args = 0, .ptr = {.gui_ptr = gui_get_time_unit}},
    {.command = "sst", .nb_args = 1, .ptr = {.gui_ptr = gui_set_time_unit}}};
