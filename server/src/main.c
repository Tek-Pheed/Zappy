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

static int check_all_args(const int flags[6])
{
    for (int i = 0; i != 6; i++) {
        if (flags[i] != 1)
            return 84;
    }
    return 0;
}

static void parse_freq(server_t *serv, int flags[6])
{
    serv->freq = atoi(optarg);
    flags[5] = 1;
}

static void check_opt(int opt, server_t *serv, int flags[6])
{
    if (opt == 'p')
        parse_port(serv, flags);
    if (opt == 'x')
        parse_res_x(serv, flags);
    if (opt == 'y')
        parse_res_y(serv, flags);
    if (opt == 'c')
        parse_client_nb(serv, flags);
    if (opt == 'f')
        parse_freq(serv, flags);
}

static int parse_args(int argc, char *const argv[], server_t *serv)
{
    int opt = getopt(argc, argv, "p:x:y:n:c:f:v");
    int flags[6] = {0};

    while (opt != -1) {
        if (opt == 'n')
            parse_team_name(serv, flags, argc, argv);
        if (opt == 'v')
            serv->verbose = true;
        if (opt == '?')
            return 84;
        check_opt(opt, serv, flags);
        opt = getopt(argc, argv, "p:x:y:n:c:f:v");
    }
    return check_all_args(flags);
}

static int display_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2");
    printf(" ... -c clientsNb -f freq [-v verbose true|false]\n");
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

static void print_serv(const server_t *serv)
{
    team_t *tmp;
    int team_len = list_get_size(serv->teams);

    printf("P: %d\n", serv->port);
    printf("X: %d\n", serv->resX);
    printf("Y: %d\n", serv->resY);
    for (int i = 0; i != team_len; i++) {
        tmp = list_get_elem_at_position(serv->teams, i);
        if (tmp == NULL)
            continue;
        printf("N: %s\n", tmp->name);
    }
    printf("C: %d\n", serv->clientNb);
    printf("F: %d\n", serv->freq);
    printf("Verbose: %s\n", serv->verbose ? "true" : "false");
}

int main(int argc, char *argv[])
{
    server_t *serv = init_struct();
    int retval = check_args(argc, argv, serv);

    if (retval != 0) {
        destroy_server(serv);
        return 84;
    }
    print_serv(serv);
    serv->map = create_map(serv);
    create_teams_eggs(serv);
    retval = run_server(serv);
    destroy_server(serv);
    return retval;
}
