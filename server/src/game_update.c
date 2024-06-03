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
#include <unistd.h>
#include "client.h"
#include "commands.h"
#include "server.h"

static void notify_clients(
    server_t *serv, enum client_state type, const char *message)
{
    client_t *client = NULL;
    size_t client_nb = list_get_size(serv->client);

    for (size_t i = 0; i != client_nb; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL || client->state != type)
            continue;
        server_send_data(client, message);
    }
}

static void check_player_death(server_t *serv, client_t *client)
{
    char *buff = NULL;

    if (client->player.food <= 0) {
        buff = event_player_death(client->player.number);
        notify_clients(serv, GRAPHICAL, buff);
        client->player.is_dead = true;
        server_send_data(client, "dead\n");
        free(buff);
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
        gettimeofday(&client->player.last_food_update, NULL);
    }
    check_player_death(serv, client);
}

void game_update(server_t *serv)
{
    client_t *client = NULL;
    size_t client_nb = list_get_size(serv->client);

    for (size_t i = 0; i != client_nb; i++) {
        client = list_get_elem_at_back(serv->client);
        if (client == NULL || client->state != AI || client->fd == -1)
            continue;
        update_player(serv, client);
    }
}
