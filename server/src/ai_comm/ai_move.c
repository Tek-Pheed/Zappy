/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_move
*/

#include <sys/time.h>
#include <time.h>
#include "commands.h"
#include "server.h"

static void send_update(server_t *serv, client_t *cli)
{
    server_send_data(cli, "ok\n");
    event_player_position(serv, cli);
}

bool ai_move_forward(
    server_t *serv, client_t *cli, UNUSED const char *obj)
{
    serv->map[cli->player.x][cli->player.y].nb_player_on -= 1;
    if (cli->player.orient == NORTH)
        cli->player.y =
            cli->player.y == 0 ? serv->resY - 1 : cli->player.y - 1;
    if (cli->player.orient == SOUTH)
        cli->player.y =
            cli->player.y == serv->resY - 1 ? 0 : cli->player.y + 1;
    if (cli->player.orient == EAST)
        cli->player.x =
            cli->player.x == serv->resX - 1 ? 0 : cli->player.x + 1;
    if (cli->player.orient == WEST)
        cli->player.x =
            cli->player.x == 0 ? serv->resX - 1 : cli->player.x - 1;
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    serv->map[cli->player.x][cli->player.y].nb_player_on += 1;
    send_update(serv, cli);
    return true;
}

// clang-format off
bool ai_turn_right(
    server_t *serv, client_t *cli, UNUSED const char *obj)
{
    switch (cli->player.orient) {
        case NORTH:
            cli->player.orient = EAST;
            break;
        case EAST:
            cli->player.orient = SOUTH;
            break;
        case SOUTH:
            cli->player.orient = WEST;
            break;
        case WEST:
            cli->player.orient = NORTH;
            break;
        default:
            return false;
    }
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    send_update(serv, cli);
    return true;
}

bool ai_turn_left(UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    switch (cli->player.orient) {
        case NORTH:
            cli->player.orient = WEST;
            break;
        case WEST:
            cli->player.orient = SOUTH;
            break;
        case SOUTH:
            cli->player.orient = EAST;
            break;
        case EAST:
            cli->player.orient = NORTH;
            break;
        default:
            return false;
    }
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    send_update(serv, cli);
    return true;
}
