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

static void create_team(server_t *serv, int flags[6])
{
    team_t *team = NULL;

    for (int i = 0; serv->tName[i] != NULL; i++) {
        team = calloc(1, sizeof(team_t));
        team->name = strdup(serv->tName[i]);
        team->nb_player = 0;
        team->eggs = calloc(1, sizeof(list_t));
        list_add_elem_at_back(&serv->teams, team);
    }
    flags[3] = 1;
}

void parse_team_name(
    server_t *serv, int flags[6], int argc, char *const argv[])
{
    size_t allocated_size = 2;
    size_t current_size = 0;
    char **newtName = NULL;

    serv->tName = calloc(allocated_size, sizeof(char *));
    if (serv->tName == NULL)
        return;
    serv->tName[current_size] = strdup(optarg);
    current_size++;
    for (; optind < argc && *argv[optind] != '-'; optind++) {
        if (current_size >= allocated_size - 1) {
            allocated_size *= 2;
            newtName = realloc(serv->tName, allocated_size * sizeof(char *));
            serv->tName = newtName;
        }
        serv->tName[current_size] = strdup(argv[optind]);
        current_size++;
    }
    serv->tName[current_size] = NULL;
    create_team(serv, flags);
}

void parse_port(server_t *serv, int flags[6])
{
    serv->port = atoi(optarg);
    flags[0] = 1;
}

void parse_res_x(server_t *serv, int flags[6])
{
    serv->resX = atoi(optarg);
    flags[1] = 1;
}

void parse_res_y(server_t *serv, int flags[6])
{
    serv->resY = atoi(optarg);
    flags[2] = 1;
}

void parse_client_nb(server_t *serv, int flags[6])
{
    serv->clientNb = atoi(optarg);
    flags[4] = 1;
}
