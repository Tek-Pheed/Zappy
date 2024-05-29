/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_handling
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include "list.h"
#include "server.h"
#include "client_handler.h"
#include "strings_array.h"

void server_send_data(client_t *client, const char *data)
{
    if (client->write_buffer[0] == '\0') {
        strcpy(client->write_buffer, data);
    } else if (strlen(client->write_buffer) + strlen(client->read_buffer)
        < BUFFER_MAX_SIZE) {
        strcat(client->write_buffer, data);
    }
}

void handle_login_request(UNUSED server_t *serv, client_t *client)
{
    if (client->state == CREATED) {
        strcpy(client->team_name, client->read_buffer);
        if (strncmp(client->read_buffer, "GRAPHIC", 7) == 0) {
            client->state = GRAPHICAL;
        } else {
            client->state = AI;
        }
    }
}

static void handle_error(bool success, client_t *client)
{
    if (!success)
        server_send_data(client, "ko\n");
}

static double get_milliseconds(struct timeval tv)
{
    return (tv.tv_sec) * 1000.0f + (tv.tv_usec) / 1000.0f;
}

static bool is_client_ready(server_t *serv, client_t *client)
{
    struct timeval current_time;
    double ready_time = get_milliseconds(client->last_cmd_time)
        + ((double) client->cmd_duration / serv->freq);

    gettimeofday(&current_time, NULL);
    return (ready_time < get_milliseconds(current_time));
}

static bool handle_commands(server_t *serv, client_t *client)
{
    size_t nb_commands = list_get_size(client->cmds);
    char *cmd = NULL;
    bool result = false;

    for (size_t i = 0; i < nb_commands; i++) {
        if (!is_client_ready(serv, client))
            break;
        cmd = list_get_elem_at_position(client->cmds, i);
        if (cmd == NULL)
            continue;
        result = run_command(serv, client, cmd);
        list_del_elem_at_position(&client->cmds, i);
        free(cmd);
        if (!result)
            break;
    }
    return (result);
}

void run_client_commands(server_t *serv)
{
    client_t *client = NULL;
    size_t nb_clients = list_get_size(serv->client);

    for (size_t i = 0; i != nb_clients; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL)
            continue;
        handle_error(handle_commands(serv, client), client);
    }
}

static void add_client_command(client_t *client)
{
    char **cmds = NULL;

    if (client->read_buffer[0] == '\0')
        return;
    cmds = str_to_array(client->read_buffer, "\n", MAX_CONCURENT_COMMANDS);
    for (size_t i = 0; cmds[i] != NULL; i++)
        list_add_elem_at_back(&client->cmds, cmds[i]);
    free(cmds);
    memset(client->read_buffer, 0, sizeof(client->read_buffer));
}

void read_client_data(server_t *serv, fd_set *read_set)
{
    client_t *client = NULL;
    list_t *clients = serv->client;
    size_t clients_nb = list_get_size(clients);

    for (size_t i = 0; i != clients_nb; i++) {
        client = list_get_elem_at_position(clients, i);
        if (client == NULL || client->fd == -1)
            continue;
        if (FD_ISSET(client->fd, read_set)) {
            memset(client->read_buffer, 0, sizeof(client->read_buffer));
            read(client->fd, client->read_buffer, sizeof(client->read_buffer));
            add_client_command(client);
        }
    }
}
