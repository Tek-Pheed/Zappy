/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#pragma once
#include <sys/select.h>
#include <sys/time.h>
#include "client.h"
#include "define.h"
#include "list.h"
#include "map.h"

#define ENABLE_LOG true

enum log_level {
    INFO,
    WARNING,
    EVENT,
    RECEIVING,
    PROCESS,
    SENDING
};

struct server_s {
    int port;
    int resX;
    int resY;
    char **tName;
    int clientNb;
    int freq;
    int socket;
    bool verbose;
    list_t *client;
    cell_t **map;
    list_t *teams;
    struct timeval last_map_update;
    char *winner;
};

server_t *init_struct(void);
void parse_team_name(
    server_t *serv, int flags[6], int argc, char *const argv[]);
void parse_client_nb(server_t *serv, int flags[6]);
void parse_res_y(server_t *serv, int flags[6]);
void parse_res_x(server_t *serv, int flags[6]);
void parse_port(server_t *serv, int flags[6]);

void destroy_server(server_t *serv);
bool server_loop(server_t *serv);
int run_server(server_t *serv);
int get_team_nb(const server_t *serv);
void server_send_data(client_t *client, const char *data);

bool server_add_client(server_t *serv);
void server_send_data(client_t *client, const char *data);
bool handle_client_login(server_t *serv, client_t *client, const char *cmd);
bool run_command(server_t *serv, client_t *client, const char *cmd);

void handle_destroyed_clients(server_t *server);
void send_buffered_data(server_t *server, fd_set *write_fds);
void read_client_data(server_t *serv, fd_set *read_set);
void game_update(server_t *serv);
double timeval_get_milliseconds(const struct timeval *tv);

bool time_is_ready(double time_ready);
bool team_remove_client(server_t *serv, const client_t *client);
bool team_add_client(server_t *serv, client_t *client);
int server_log(const server_t *serv, enum log_level level, int client_fd,
    const char *data);
