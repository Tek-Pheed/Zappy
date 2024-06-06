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

static fvect2d_t get_multiplier(int dir)
{
    switch (dir) {
        case NORTH:
            return ((fvect2d_t){0, -1});
        case WEST:
            return ((fvect2d_t){-1, 0});
        case SOUTH:
            return ((fvect2d_t){0, 1});
        case EAST:
            return ((fvect2d_t){1, 0});
        default:
            break;
    }
    return ((fvect2d_t){0, 1});
}

static int map_to_local_player_direction(
    const ivect2D_t *pos, const player_t *player)
{
    int dir = 0;
    fvect2d_t vect = {(float) pos->x - (float) player->x,
        (float) pos->y - (float) player->y};
    fvect2d_t orient = get_multiplier(player->orient);
    float angle = atan2f(orient.y, orient.x) - atan2f(vect.y, vect.x);

    angle = angle * 360.0f / (2.0f * M_PI);
    if (angle < 0.0f)
        angle += 360;
    dir = roundf(angle / 45.0f) + 1;
    printf("Position: %d %d\n", pos->x, pos->y);
    printf("Vect: %f %f\n", vect.x, vect.y);
    printf("Orient: %f %f\n", orient.x, orient.y);
    printf("Dir: %d\nAngle: %f\n", dir, angle);
    return (dir);
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
        printf("Compute offset %d: %d\n", i, tmp);
        if (tmp < dist) {
            printf("This is the smallest: %d\n", i);
            dist = tmp;
            offset = i;
        }
    }
    return (offset * (-1));
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
    offsets.y = offsets.y * -1;
    return (get_orient(&offsets, a, b));
}

void send_broadcast(client_t *target, const char *msg, int tile)
{
    char *tmp = NULL;

    if (msg == NULL)
        return;
    tmp = calloc(strlen(msg) + 32, sizeof(char));
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
