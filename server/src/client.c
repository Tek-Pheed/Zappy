/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#include "client.h"
#include <netinet/ip.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include "define.h"
#include "list.h"
#include "server.h"

void destroy_client(server_t *serv, client_t *client)
{
    size_t nb_cmds = 0;
    char *cmd = NULL;

    if (client == NULL)
        return;
    if (client->fd != -1)
        close(client->fd);
    nb_cmds = list_get_size(client->cmds);
    for (size_t i = 0; i != nb_cmds; i++) {
        cmd = list_get_elem_at_position(client->cmds, i);
        if (cmd == NULL)
            continue;
        free(cmd);
    }
    team_remove_client(serv, client);
    free(client);
}

static void send_login_answer(server_t *serv, client_t *client)
{
    char buffer[128];
    team_t *team = team_get_client(serv, client);
    int free_space = team_get_free_space(team);

    memset(buffer, '\0', sizeof(buffer));
    sprintf(buffer, "%d\n%d %d\n", free_space, serv->resX, serv->resY);
    server_send_data(client, buffer);
}

static bool create_player(server_t *serv, client_t *client, int index)
{
    client->player.food = 10;
    client->player.elevating = false;
    client->player.level = 1;
    client->player.number = index;
    client->player.orient = 1;
    gettimeofday(&client->player.last_food_update, NULL);
    return (team_add_client(serv, client));
}

bool handle_client_login(server_t *serv, client_t *client, const char *cmd)
{
    static int player_index = 0;

    if (cmd[0] == '\0')
        return (false);
    strcpy(client->team_name, cmd);
    if (strncmp(cmd, "GRAPHIC", 7) == 0) {
        client->state = GRAPHICAL;
        server_log(EVENT, client->fd, "logged in as GRAPHIC");
        return (true);
    }
    if (!create_player(serv, client, player_index)) {
        server_log(WARNING, 0, "Unable to create player in team");
        client->state = CREATED;
        return (false);
    }
    client->state = AI;
    player_index++;
    send_login_answer(serv, client);
    server_log(EVENT, client->fd, "logged in as AI");
    return (true);
}

bool server_add_client(server_t *serv)
{
    struct sockaddr_in clientAddr;
    socklen_t clientSockLen = sizeof(clientAddr);
    client_t *user = calloc(1, sizeof(client_t));

    if (user == NULL)
        return false;
    user->fd =
        accept(serv->socket, (struct sockaddr *) &clientAddr, &clientSockLen);
    if (user->fd == -1) {
        free(user);
        return false;
    }
    list_add_elem_at_back(&serv->client, user);
    server_log(EVENT, user->fd, "connection request");
    strcpy(user->write_buffer, "WELCOME\n");
    user->state = CREATED;
    return (true);
}

void check_lvl_player(server_t *serv)
{
    int len = list_get_size(serv->client);
    client_t *tmp;

    for (int i = 0; i != len; i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp && tmp->state == AI && tmp->player.level == 8) {
            serv->winner = strdup(tmp->team_name);
            return;
        }
    }
}
