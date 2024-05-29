/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** gui_comm2
*/

#include <stdlib.h>
#include "server.h"
#include "command_handler.h"

bool gui_player_position(server_t *server, client_t *client, char **args)
{
    char *buff = NULL;
    int number = 0;

    number = atoi(args[1]);
    buff = player_position(server, number);
    server_send_data(client, buff);
    free(buff);
    return (true);
}

bool gui_player_level(server_t *server, client_t *client, char **args)
{
    char *buff = NULL;
    int number = 0;

    number = atoi(args[1]);
    buff = player_level(server, number);
    server_send_data(client, buff);
    free(buff);
    return (true);
}

bool gui_player_inventory(server_t *server, client_t *client, char **args)
{
    char *buff = NULL;
    int number = 0;

    number = atoi(args[1]);
    buff = player_inventory(server, number);
    server_send_data(client, buff);
    free(buff);
    return (true);
}

bool gui_get_time_unit(server_t *server, client_t *client, UNUSED char **args)
{
    char *buff = NULL;

    buff = time_unit_request(server);
    server_send_data(client, buff);
    free(buff);
    return (true);
}

bool gui_set_time_unit(server_t *server, client_t *client, char **args)
{
    char *buff = NULL;
    int number = 0;

    number = atoi(args[1]);
    buff = time_unit_modif(server, number);
    server_send_data(client, buff);
    free(buff);
    return (true);
}
