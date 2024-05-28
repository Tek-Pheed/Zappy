/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#pragma once
#define OFFSET_ARGS           8
#define UNUSED                __attribute__((unused))
#define CONN_TIMEOUT_DELAY_US 25000000
#define LINEMATE              0
#define DERAUMERE             1
#define SIBUR                 2
#define MENDIANE              3
#define PHIRAS                4
#define THYSTAME              5
#define LINEMATE_R            0.3
#define DERAUMERE_R           0.15
#define SIBUR_R               0.1
#define MENDIANE_R            0.1
#define PHIRAS_R              0.08
#define THYSTAME_R            0.05
#define FOOD_R                0.5
#include "list.h"

typedef struct cell_s cell_t;
typedef struct server_s server_t;

struct server_s {
    int port;
    int resX;
    int resY;
    char **tName;
    int clientNb;
    int freq;
    int socket;
    list_t *client;
    cell_t **map;
};
server_t *init_struct(void);
void parse_team_name(server_t *serv, int flags[6], int argc, char *argv[]);
void parse_client_nb(server_t *serv, int flags[6]);
void parse_res_y(server_t *serv, int flags[6]);
void parse_res_x(server_t *serv, int flags[6]);
void parse_port(server_t *serv, int flags[6]);
void free_struct(server_t *serv);
struct client_s {
    int fd;
};
typedef struct client_s client_t;
int server_loop(server_t *serv);
struct cell_s {
    int food;
    int stone[6];
    bool is_player_on;
};
cell_t **create_map(server_t *serv);
void free_map(server_t *serv);
