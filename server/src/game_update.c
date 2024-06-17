/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game_update
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "client.h"
#include "commands.h"
#include "server.h"

static void check_player_death(const server_t *serv, client_t *client)
{
    if (client->player.food <= 0) {
        event_player_death(serv, client);
        client->player.is_dead = true;
        serv->map[client->player.x][client->player.y].nb_player_on--;
        return;
    }
}

static void update_player(server_t *serv, client_t *client)
{
    double target_time = 0;
    struct timeval tv;

    if (client->player.is_dead)
        return;
    target_time = timeval_get_milliseconds(&client->player.last_food_update)
        + ((126.0 / serv->freq) * 1000.0);
    gettimeofday(&tv, NULL);
    if (target_time <= timeval_get_milliseconds(&tv)) {
        client->player.food--;
        event_player_inventory(serv, client);
        gettimeofday(&client->player.last_food_update, NULL);
    }
    check_player_death(serv, client);
}

static void update_map(server_t *serv)
{
    double target_time = 0;
    struct timeval tv;
    float quant[7] = {0};

    if (serv->winner != NULL)
        return;
    target_time = timeval_get_milliseconds(&serv->last_map_update)
        + ((20.0 / serv->freq) * 1000.0);
    gettimeofday(&tv, NULL);
    if (target_time <= timeval_get_milliseconds(&tv)) {
        calculate_quantity_after(serv, quant);
        for (int i = 0; i != 7; i++)
            distribute_items_after(serv->map, serv, quant[i], i);
        gettimeofday(&serv->last_map_update, NULL);
    }
}

void game_update(server_t *serv)
{
    client_t *client = NULL;
    size_t client_nb = list_get_size(serv->client);

    for (size_t i = 0; i != client_nb; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL || client->state != AI || client->fd == -1)
            continue;
        update_player(serv, client);
    }
    update_map(serv);
}
