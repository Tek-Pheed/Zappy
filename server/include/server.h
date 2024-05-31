/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#pragma once
#include <sys/time.h>
#include "client.h"
#include "define.h"
#include "list.h"
#include "map.h"

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
    list_t *teams;
    char *winner;
};

server_t *init_struct(void);
void parse_team_name(server_t *serv, int flags[6], int argc, char *argv[]);
void parse_client_nb(server_t *serv, int flags[6]);
void parse_res_y(server_t *serv, int flags[6]);
void parse_res_x(server_t *serv, int flags[6]);
void parse_port(server_t *serv, int flags[6]);
void free_struct(server_t *serv);

int server_loop(server_t *serv);
int run_server(server_t *serv);
int get_team_nb(server_t *serv);
void server_send_data(client_t *client, const char *data);
void destroy_server(server_t *serv);
void send_login_answer(server_t *serv, client_t *client);
