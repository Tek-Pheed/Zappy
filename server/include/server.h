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
#define linemate              0
#define deraumere             1
#define sibur                 2
#define mendiane              3
#define phiras                4
#define thystame              5
#define linemate_r            0.3
#define deraumere_r           0.15
#define sibur_r               0.1
#define mendiane_r            0.1
#define phiras_r              0.08
#define thystame_r            0.05
#define food_r                0.5
#include "list.h"

struct server_s {
    int port;
    int resX;
    int resY;
    char **tName;
    int clientNb;
    int freq;
    int socket;
    list_t *client;
};
typedef struct server_s server_t;
server_t *init_struct(void);
void parse_team_name(server_t *serv, int flags[6], int argc, char *argv[]);
void parseclientNb(server_t *serv, int flags[6]);
void parseresY(server_t *serv, int flags[6]);
void parseresX(server_t *serv, int flags[6]);
void parseport(server_t *serv, int flags[6]);
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
typedef struct cell_s cell_t;
