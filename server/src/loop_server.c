/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** loop_server
*/

#include <netinet/ip.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include "define.h"
#include "list.h"
#include "server.h"
#include "commands.h"

static void zero_fds(fd_set *a, fd_set *b)
{
    FD_ZERO(a);
    FD_ZERO(b);
}

static void set_fd(server_t *serv, fd_set *rfds, fd_set *wfds)
{
    client_t *client;
    size_t list_size = list_get_size(serv->client);

    zero_fds(rfds, wfds);
    for (size_t i = 0; i != list_size; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL || client->fd < 1)
            continue;
        FD_SET(client->fd, rfds);
        if (client->write_buffer[0] != '\0')
            FD_SET(client->fd, wfds);
    }
    FD_SET(serv->socket, rfds);
}

static void remove_old_clients(server_t *serv)
{
    client_t *client = NULL;
    list_t *clients = serv->client;
    size_t clients_nb = list_get_size(clients);

    for (size_t i = 0; i != clients_nb; i++) {
        client = list_get_elem_at_position(clients, i);
        if (client == NULL)
            continue;
        if (client->state == AI && client->player.is_dead){
            close(client->fd);
            client->fd = -1;
        }
        if (client->fd == -1) {
            list_del_elem_at_position(&serv->client, i);
            destroy_client(serv, client);
            i--;
        }
    }
}

static void send_win(server_t *serv, const char *win_msg)
{
    size_t client_nb = list_get_size(serv->client);
    client_t *client = NULL;

    for (size_t i = 0; i != client_nb; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL || client->state != GRAPHICAL)
            continue;
        server_send_data(client, win_msg);
    }
}

static bool check_win(server_t *serv)
{
    char *win_buff = NULL;

    if (serv->winner != NULL) {
        win_buff = event_end_game(serv->winner);
        if (win_buff == NULL)
            return (false);
        send_win(serv, win_buff);
        free(win_buff);
        return (true);
    }
    return (false);
}

bool server_loop(server_t *serv)
{
    struct timeval time = {0, (1.0f / (float) serv->freq) * 1000000};
    fd_set fdset;
    fd_set fdwset;

    set_fd(serv, &fdset, &fdwset);
    if (select(FD_SETSIZE, &fdset, &fdwset, NULL, &time) != -1) {
        send_buffered_data(serv, &fdwset);
        if (FD_ISSET(serv->socket, &fdset) != 0)
            server_add_client(serv);
        read_client_data(serv, &fdset);
    }
    run_client_commands(serv);
    remove_old_clients(serv);
    game_update(serv);
    return (check_win(serv));
}
