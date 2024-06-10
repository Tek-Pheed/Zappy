/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_fork
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "commands.h"
#include "define.h"
#include "server.h"

bool ai_end_fork(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    team_t *tmp = team_get_client(serv, cli);
    egg_t *egg = NULL;

    egg = list_get_elem_at_back(tmp->eggs);
    event_egg_laid(serv, cli, egg->number, &((ivect2D_t){egg->x, egg->y}));
    server_send_data(cli, "ok\n");
    return true;
}

bool ai_fork(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    team_t *tmp = team_get_client(serv, cli);
    egg_t *egg = NULL;

    if (!tmp)
        return false;
    event_egg_laying(serv, cli);
    egg = create_egg(cli->player.x, cli->player.y, tmp);
    cli->cmd_duration = 42;
    gettimeofday(&cli->last_cmd_time, NULL);
    list_add_elem_at_back(&tmp->eggs, egg);
    server_send_data(cli, "ok\n");
    list_add_elem_at_position(&cli->cmds, strdup("EndForkServer\n"), 2);
    return true;
}
