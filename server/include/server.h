/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#pragma once
#include <sys/time.h>
#include <sys/select.h>
#include "client.h"
#include "define.h"
#include "list.h"
#include "map.h"

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

void destroy_server(server_t *serv);
int server_loop(server_t *serv);
int run_server(server_t *serv);
int get_team_nb(server_t *serv);
void server_send_data(client_t *client, const char *data);

bool server_add_client(server_t *serv);
void server_send_data(client_t *client, const char *data);
bool handle_client_login(server_t *serv, client_t *client, const char *cmd);
bool run_command(server_t *serv, client_t *client, const char *cmd);

void handle_destroyed_clients(server_t *server);
void send_buffered_data(server_t *server, fd_set *write_fds);
void read_client_data(server_t *serv, fd_set *read_set);
void game_update(server_t *serv);
double timeval_get_milliseconds(struct timeval *tv);

bool time_is_ready(double time_ready);
