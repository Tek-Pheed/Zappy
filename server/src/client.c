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
#include "commands.h"
#include "define.h"
#include "list.h"
#include "server.h"

void destroy_client(server_t *serv, client_t *client)
{
    size_t nb_cmds = 0;
    char *cmd = NULL;

    if (client == NULL)
        return;
    if (client->fd != -1) {
        if (client->state == AI && !client->player.is_dead)
            event_player_death(serv, client);
        close(client->fd);
    }
    nb_cmds = list_get_size(client->cmds);
    for (size_t i = 0; i != nb_cmds; i++) {
        cmd = list_get_elem_at_position(client->cmds, i);
        if (cmd == NULL)
            continue;
        free(cmd);
    }
    list_clear(&client->cmds);
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
    client->player.elevating = -1;
    client->player.level = 1;
    client->player.number = index;
    client->player.orient = 1;
    gettimeofday(&client->player.last_food_update, NULL);
    return (team_add_client(serv, client));
}

static void send_initial_gui_data(server_t *serv, client_t *client)
{
    client_t *cli = NULL;
    char buff[BUFFER_MAX_SIZE + 100];

    server_log(serv, EVENT, client->fd, "logged in as GRAPHIC");
    event_teams_names(serv, client);
    gui_get_time_unit(serv, client, NULL);
    gui_map_size(serv, client, NULL);
    gui_map_content(serv, client, NULL);
    for (size_t i = 0; i != list_get_size(serv->client); i++) {
        cli = list_get_elem_at_position(serv->client, i);
        if (cli == NULL || cli->state != AI)
            continue;
        memset(buff, 0, sizeof(buff));
        sprintf(buff, "pnw %d %d %d %d %d %s\n", cli->player.number,
            cli->player.x, cli->player.y, cli->player.orient,
            cli->player.level, cli->team_name);
        server_send_data(client, buff);
    }
}

bool handle_client_login(server_t *serv, client_t *client, const char *cmd)
{
    static int player_index = 0;

    if (cmd[0] == '\0')
        return (false);
    strcpy(client->team_name, cmd);
    if (strncmp(cmd, "GRAPHIC", 7) == 0) {
        client->state = GRAPHICAL;
        send_initial_gui_data(serv, client);
        return (true);
    }
    if (!create_player(serv, client, player_index)) {
        server_log(serv, WARNING, 0, "Unable to create player in team");
        return (false);
    }
    client->state = AI;
    player_index++;
    send_login_answer(serv, client);
    event_connnew_player(serv, client);
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
    server_log(serv, INFO, user->fd, "user connection request");
    strcpy(user->write_buffer, "WELCOME\n");
    user->state = CREATED;
    return (true);
}

static void check_win_team(server_t *serv)
{
    int len_team = list_get_size(serv->teams);
    team_t *tmp = NULL;

    for (int i = 0; i != len_team; i++) {
        tmp = list_get_elem_at_position(serv->teams, i);
        if (tmp == NULL)
            continue;
        if (tmp->nb_level_max >= 6) {
            serv->winner = strdup(tmp->name);
            return;
        }
    }
}

void check_lvl_player(server_t *serv)
{
    int len = list_get_size(serv->client);
    client_t *tmp;
    team_t *team_tmp;

    for (int i = 0; i != len; i++) {
        tmp = list_get_elem_at_position(serv->client, i);
        if (tmp == NULL)
            continue;
        if (tmp && tmp->state == AI && tmp->player.level == 8) {
            team_tmp = team_get_client(serv, tmp);
            team_tmp->nb_level_max += 1;
        }
    }
    check_win_team(serv);
}
