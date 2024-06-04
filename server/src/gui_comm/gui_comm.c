/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** gui_comm
*/

#include <stdlib.h>
#include "server.h"
#include "commands.h"

bool gui_map_size(server_t *server, client_t *client, UNUSED char **args)
{
    char *buff = map_size(server);

    if (buff == NULL)
        return (false);
    server_send_data(client, buff);
    free(buff);
    return (true);
}

bool gui_tile_content(server_t *server, client_t *client, char **args)
{
    char *buff = NULL;
    int x = 0;
    int y = 0;

    if (args[1] != NULL)
        x = atoi(args[1]);
    if (args[2] != NULL)
        y = atoi(args[2]);
    buff = tile_content(server, x, y);
    if (buff == NULL)
        return (false);
    server_send_data(client, buff);
    return (true);
}

bool gui_map_content(server_t *server, client_t *client, UNUSED char **args)
{
    char *buff = NULL;

    buff = all_content(server);
    if (buff == NULL)
        return (false);
    server_send_data(client, buff);
    free(buff);
    return (true);
}

bool gui_all_name(server_t *server, client_t *client, UNUSED char **args)
{
    char *buff = NULL;

    buff = all_name(server);
    if (buff == NULL)
        return (false);
    server_send_data(client, buff);
    return (true);
}
