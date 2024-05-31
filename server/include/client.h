/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once
#include <stdbool.h>
#include "define.h"
#include "list.h"
#include "server.h"

// clang-format off
enum client_state {
    CREATED,
    AI,
    GRAPHICAL
};
// clang-format on

struct player_s {
    char team_name[BUFFER_MAX_SIZE];
    int x;
    int y;
    int food;
    int stone[6];
    int level;
    int orient;
    int number;
    bool elevating;
};

struct client_s {
    int fd;
    char write_buffer[BUFFER_MAX_SIZE];
    char read_buffer[BUFFER_MAX_SIZE];
    char team_name[BUFFER_MAX_SIZE];
    enum client_state state;
    player_t player;
    list_t *cmds;
    struct timeval last_cmd_time;
    int cmd_duration;
};

struct team_s {
    char *name;
    int nb_player;
    list_t *eggs;
};
team_t *get_team_client(server_t *serv, client_t *cli);
int get_free_space_team(team_t *team);
void destroy_client(client_t *client);

struct egg_s {
    int x;
    int y;
    team_t *team;
};
void check_lvl_player(server_t *serv);
