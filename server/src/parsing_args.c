/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parsing_args
*/

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

extern char *optarg;
extern int optind, opterr, optopt;

void parse_team_name(server_t *serv, int flags[6], int argc, char *argv[])
{
    size_t allocated_size = 2;
    size_t current_size = 0;
    char **new_tName = NULL;

    serv->_tName = calloc(allocated_size, sizeof(char *));
    if (serv->_tName == NULL)
        return;
    serv->_tName[current_size] = strdup(optarg);
    current_size++;
    for (; optind < argc && *argv[optind] != '-'; optind++) {
        if (current_size >= allocated_size - 1) {
            allocated_size *= 2;
            new_tName = realloc(serv->_tName, allocated_size * sizeof(char *));
            serv->_tName = new_tName;
        }
        serv->_tName[current_size] = strdup(argv[optind]);
        current_size++;
    }
    serv->_tName[current_size] = NULL;
    flags[3] = 1;
}

void parse_port(server_t *serv, int flags[6])
{
    serv->_port = atoi(optarg);
    flags[0] = 1;
}

void parse_resx(server_t *serv, int flags[6])
{
    serv->_resX = atoi(optarg);
    flags[1] = 1;
}

void parse_resy(server_t *serv, int flags[6])
{
    serv->_resY = atoi(optarg);
    flags[2] = 1;
}

void parse_clientnb(server_t *serv, int flags[6])
{
    serv->_clientNb = atoi(optarg);
    flags[4] = 1;
}
