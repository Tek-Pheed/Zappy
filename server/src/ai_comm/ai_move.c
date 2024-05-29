/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_move
*/

#include <sys/time.h>
#include <time.h>
#include "server.h"

bool ai_move_forward(
    UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    if (cli->player->orient == NORTH)
        cli->player->y =
            cli->player->y == 0 ? serv->resY - 1 : cli->player->y - 1;
    if (cli->player->orient == SOUTH)
        cli->player->y =
            cli->player->y == serv->resY - 1 ? 0 : cli->player->y + 1;
    if (cli->player->orient == EAST)
        cli->player->x =
            cli->player->x == serv->resX - 1 ? 0 : cli->player->x + 1;
    if (cli->player->orient)
        cli->player->x =
            cli->player->x == 0 ? serv->resX - 1 : cli->player->x - 1;
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    server_send_data(cli, "ok\n");
    return true;
}

bool ai_turn_right(
    UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    if (cli->player->orient == NORTH)
        cli->player->orient += 1;
    if (cli->player->orient == SOUTH)
        cli->player->orient += 1;
    if (cli->player->orient == EAST)
        cli->player->orient += 1;
    if (cli->player->orient == WEST)
        cli->player->orient = 1;
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    server_send_data(cli, "ok\n");
    return true;
}

bool ai_turn_left(UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    if (cli->player->orient == NORTH)
        cli->player->orient = 4;
    if (cli->player->orient == SOUTH)
        cli->player->orient -= 1;
    if (cli->player->orient == EAST)
        cli->player->orient -= 1;
    if (cli->player->orient == WEST)
        cli->player->orient -= 1;
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    server_send_data(cli, "ok\n");
    return true;
}
