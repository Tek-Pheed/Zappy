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
#include "list.h"

struct server_s {
    int _port;
    int _resX;
    int _resY;
    char **_tName;
    int _clientNb;
    int _freq;
    int socket;
    list_t *client;
};
typedef struct server_s server_t;
server_t *init_struct(void);
void parse_team_name(server_t *serv, int flags[6], int argc, char *argv[]);
void parse_clientnb(server_t *serv, int flags[6]);
void parse_resy(server_t *serv, int flags[6]);
void parse_resx(server_t *serv, int flags[6]);
void parse_port(server_t *serv, int flags[6]);
void free_struct(server_t *serv);
struct client_s {
    int fd;
};
typedef struct client_s client_t;
int server_loop(server_t *serv);
