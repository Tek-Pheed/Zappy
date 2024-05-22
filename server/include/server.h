/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#pragma once
#define OFFSET_ARGS 8

struct server_s {
    int _port;
    int _resX;
    int _resY;
    char **_tName;
    int _clientNb;
    int _freq;
};
typedef struct server_s server_t;
server_t *init_struct(void);
void parse_team_name(server_t *serv, int flags[6], int argc, char *argv[]);
