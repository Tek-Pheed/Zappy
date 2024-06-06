/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** gui_update
*/

#include <stdlib.h>
#include "commands.h"
#include "define.h"
#include "server.h"

void event_player_position(server_t *serv, const client_t *client)
{
    char *buff = player_position(serv, client->player.number);

    if (buff == NULL)
        return;
    server_log(serv, EVENT, client->fd, "player position changed");
    server_event_send_many(serv, GRAPHICAL, buff);
    free(buff);
}

void event_player_level(server_t *serv, const client_t *client)
{
    char *buff = player_level(serv, client->player.number);

    if (buff == NULL)
        return;
    server_log(serv, EVENT, client->fd, "player changed level");
    server_event_send_many(serv, GRAPHICAL, buff);
    free(buff);
}

void event_player_inventory(server_t *serv, const client_t *client)
{
    char *buff = player_inventory(serv, client->player.number);

    if (buff == NULL)
        return;
    server_log(serv, EVENT, client->fd, "player inventory changed");
    server_event_send_many(serv, GRAPHICAL, buff);
    free(buff);
}

void event_teams_names(server_t *serv, client_t *client)
{
    char *buff = all_name(serv);

    if (buff == NULL)
        return;
    server_send_data(client, buff);
    server_log(serv, INFO, client->fd, "Sending team names");
    free(buff);
}

void event_tile_update(const server_t *serv, int x, int y)
{
    char *tile = tile_content(serv, x, y);

    if (tile == NULL)
        return;
    server_event_send_many(serv, GRAPHICAL, tile);
    server_log(serv, INFO, 0, "Send update tile");
    free(tile);
}
