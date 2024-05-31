/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_broadcast
*/

#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "server.h"

// Wait follow-ip todo

static int map_to_local_player_direction(ivect2D_t *pos, player_t *player)
{
    fvect2D_t vect = {(float) player->x - (float) pos->x,
        (float) player->y - (float) pos->y};

    if (vect.x == 0.0f && vect.y == 0.0f)
        return (0);

    float angle = atan2f(vect.y, vect.x) * 180.0f / M_PI;
    angle += (player->orient - 1) * 90.0f;
    int dir = (angle / 45.0f) + 1;
    if (angle < 0.0f)
        dir = 8 - dir;
    return (dir);
}

static bool is_out_of_bounds(server_t *serv, ivect2D_t *pos)
{
    if (pos->x >= serv->resX || pos->y >= serv->resY)
        return (true);
    return (false);
}

static ivect2D_t get_pos_in_bounds(server_t *serv, ivect2D_t *pos)
{
    return ((ivect2D_t){pos->x % (serv->resX), pos->y % (serv->resY)});
}

list_t get_players_on_cell(server_t *serv, ivect2D_t *world_pos)
{
    list_t lst = {NULL, NULL};
    list_t *lptr = &lst;
    client_t *client = NULL;
    size_t clients = list_get_size(serv->client);

    for (size_t i = 0; i != clients; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL || client->state != AI)
            continue;
        if (client->player.x == world_pos->x
            && client->player.y == world_pos->y)
            list_add_elem_at_back(&lptr, &client);
    }
    return (lst);
}

static bool broadcast_cell(
    server_t *serv, client_t *cli, ivect2D_t *cell_pos, ivect2D_t *prev_pos)
{
    ivect2D_t position = get_pos_in_bounds(serv, cell_pos);
    list_t player_lst = get_players_on_cell(serv, &position);
    size_t players = list_get_size(&player_lst);
    client_t *client = NULL;

    if (players == 0)
        return (false);
    for (size_t i = 0; i != players; i++) {
        client = list_get_elem_at_position(&player_lst, i);
        if (client == NULL)
            continue;
        server_send_data();
    }
    return (true);
}

bool trace_square(server_t *serv, client_t *cli, const char *obj)
{
    size_t square_size = 0;

    for (square_size = 0; square_size < serv->resX || square_size < serv->resY;
         square_size++) {
        /* code */
    }
}

bool ai_broadcast(server_t *serv, client_t *cli, const char *obj)
{
    // calulate all paths and get the shortest

    // send: message tile text

    if (cli->player.x)

        cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    return (true);
}
