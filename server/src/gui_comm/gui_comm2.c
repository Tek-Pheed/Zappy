/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** gui_comm2
*/

#include <stdlib.h>
#include "server.h"
#include "commands.h"

bool gui_player_position(server_t *server, client_t *client, char **args)
{
    char *buff = NULL;
    int number = 0;

    number = atoi(args[1] + 1);
    buff = player_position(server, number);
    if (buff == NULL)
        return (false);
    server_send_data(client, buff);
    free(buff);
    return (true);
}

bool gui_player_level(server_t *server, client_t *client, char **args)
{
    char *buff = NULL;
    int number = 0;

    number = atoi(args[1] + 1);
    buff = player_level(server, number);
    if (buff == NULL)
        return (false);
    server_send_data(client, buff);
    free(buff);
    return (true);
}

bool gui_player_inventory(server_t *server, client_t *client, char **args)
{
    char *buff = NULL;
    int number = 0;

    number = atoi(args[1] + 1);
    buff = player_inventory(server, number);
    if (buff == NULL)
        return (false);
    if (buff[0] == '\0') {
        free(buff);
        return (false);
    }
    server_send_data(client, buff);
    free(buff);
    return (true);
}

bool gui_get_time_unit(server_t *server, client_t *client, UNUSED char **args)
{
    char *buff = NULL;

    buff = time_unit_request(server);
    if (buff == NULL)
        return (false);
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
    if (buff == NULL)
        return (false);
    server_send_data(client, buff);
    free(buff);
    event_time_modif(server);
    return (true);
}
