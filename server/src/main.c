/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

extern char *optarg;
extern int optind, opterr, optopt;

static int check_all_args(int flags[6])
{
    for (int i = 0; i != 6; i++) {
        if (flags[i] != 1)
            return 84;
    }
    return 0;
}

static void parse_freq(server_t *serv, int flags[6])
{
    serv->_freq = atoi(optarg);
    flags[5] = 1;
}

static void check_opt(int opt, server_t *serv, int flags[6])
{
    if (opt == 'p')
        parse_port(serv, flags);
    if (opt == 'x')
        parse_resx(serv, flags);
    if (opt == 'y')
        parse_resy(serv, flags);
    if (opt == 'c')
        parse_clientnb(serv, flags);
    if (opt == 'f')
        parse_freq(serv, flags);
}

static int parse_args(int argc, char *argv[], server_t *serv)
{
    int opt = getopt(argc, argv, "p:x:y:n:c:f:");
    int flags[6] = {0};

    while (opt != -1) {
        if (opt == 'n')
            parse_team_name(serv, flags, argc, argv);
        if (opt == '?')
            return 84;
        check_opt(opt, serv, flags);
        opt = getopt(argc, argv, "p:x:y:n:c:f:");
    }
    return check_all_args(flags);
}

static int display_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2");
    printf(" ... -c clientsNb -f freq\n");
    return 1;
}

static int check_args(int argc, char *argv[], server_t *serv)
{
    if (argc == 1)
        return display_help();
    if (argc == 2 && strcmp(argv[1], "-help") == 0)
        return display_help();
    return parse_args(argc, argv, serv);
}

int main(int argc, char *argv[])
{
    server_t *serv = init_struct();
    int retval = check_args(argc, argv, serv);

    if (retval != 0)
        return 84;
    printf("P: %d\n", serv->_port);
    printf("X: %d\n", serv->_resX);
    printf("Y: %d\n", serv->_resY);
    for (int i = 0; serv->_tName[i] != NULL; i++) {
        printf("N: %s\n", serv->_tName[i]);
    }
    printf("C: %d\n", serv->_clientNb);
    printf("F: %d\n", serv->_freq);
    return 0;
}
