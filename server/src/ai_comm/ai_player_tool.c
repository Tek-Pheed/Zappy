/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_player_tool
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "server.h"

bool ai_inventory(UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    char *buff = calloc(BUFFER_MAX_SIZE, sizeof(char));

    if (!buff)
        return false;
    sprintf(buff,
        "linemate %d, deraumere %d, sibur %d, mendiane %d, phiras %d, "
        "thystame %d, food %d\n",
        cli->player->stone[LINEMATE], cli->player->stone[DERAUMERE],
        cli->player->stone[SIBUR], cli->player->stone[MENDIANE],
        cli->player->stone[PHIRAS], cli->player->stone[THYSTAME],
        cli->player->food);
    cli->cmd_duration = 1;
    gettimeofday(&cli->last_cmd_time, NULL);
    server_send_data(cli, buff);
    free(buff);
    return true;
}

bool ai_dead(UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    server_send_data(cli, "dead\n");
    return true;
}

bool ai_connect_nbr(
    UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    return true;
}
