/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_broadcast
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "commands.h"
#include "define.h"
#include "server.h"

// printf("Dir: %d\nAngle: %f\n", dir, angle);
static int map_to_local_player_direction(
    const ivect2D_t *pos, const player_t *player)
{
    int dir = 0;
    float angle = 0.0f;
    fvect2D_t vect = {(float) player->x - (float) pos->x,
        (float) player->y - (float) pos->y};

    if (vect.x == 0.0f && vect.y == 0.0f)
        return (0);
    angle = atan2f(vect.y, vect.x) * 180.0f / M_PI;
    angle += (player->orient - 1) * 90.0f;
    dir = (angle / 45.0f) + 1;
    if (angle < 0.0f)
        dir = 8 - dir;
    return (dir % 8);
}

static int get_orient(
    const ivect2D_t *offsets, const client_t *a, const client_t *b)
{
    ivect2D_t tile_pos = {0, 0};

    if (offsets->x == 0 && offsets->y == 0) {
        tile_pos.x = a->player.x;
        tile_pos.y = a->player.y;
    } else {
        tile_pos.x = b->player.x + offsets->x;
        tile_pos.y = b->player.y + offsets->y;
    }
    return (map_to_local_player_direction(&tile_pos, &b->player));
}

static int get_x_offset(
    const server_t *serv, const client_t *a, const client_t *b)
{
    int tmp = 0;
    int offset = 0;
    int dist = serv->resX * 2 + serv->resY * 2;

    for (int i = -1; i != 2; i++) {
        tmp = abs((b->player.x + i * serv->resX) - a->player.x)
            + abs((b->player.y) - a->player.y);
        if (tmp < dist) {
            dist = tmp;
            offset = i;
        }
    }
    return (offset);
}

static int get_tile_orient(
    const server_t *serv, const client_t *a, const client_t *b)
{
    int tmp = 0;
    int dist = serv->resX * 2 + serv->resY * 2;
    ivect2D_t offsets = {0, 0};

    offsets.x = get_x_offset(serv, a, b);
    for (int i = -1; i != 2; i++) {
        tmp = abs((b->player.x + offsets.x) - a->player.x)
            + abs((b->player.y + i * serv->resY) - a->player.y);
        if (tmp < dist) {
            dist = tmp;
            offsets.y = i;
        }
    }
    return (get_orient(&offsets, a, b));
}

static void send_broadcast(client_t *target, const char *msg, int tile)
{
    char *tmp = calloc(strlen(msg) + 32, sizeof(char));

    sprintf(tmp, "message %d, %s\n", tile, msg);
    server_send_data(target, tmp);
    free(tmp);
}

bool ai_broadcast(server_t *serv, client_t *cli, const char *obj)
{
    size_t players = list_get_size(serv->client);
    client_t *client = NULL;

    for (size_t i = 0; i != players; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL || client->state != AI || client == cli)
            continue;
        if (client->player.x == cli->player.x
            && client->player.y == cli->player.y) {
            send_broadcast(client, obj, 0);
            continue;
        }
        send_broadcast(client, obj, get_tile_orient(serv, cli, client));
    }
    event_broadcast(serv, cli, obj);
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    server_send_data(cli, "ok\n");
    return (true);
}