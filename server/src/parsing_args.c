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
    size_t size;

    serv->_tName = malloc(sizeof(char *) * 1);
    if (serv->_tName == NULL)
        return;
    serv->_tName[0] = strdup(optarg);
    for (; optind < argc && *argv[optind] != '-'; optind++) {
        size = malloc_usable_size(serv->_tName);
        serv->_tName = realloc(serv->_tName, size + (sizeof(char *) * 1));
        if (serv->_tName == NULL)
            return;
        serv->_tName[optind - OFFSET_ARGS] = strdup(argv[optind]);
    }
    flags[3] = 1;
}
