/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_struct
*/

#include <stdlib.h>
#include <unistd.h>
#include "server.h"

server_t *init_struct(void)
{
    server_t *tmp = calloc(1, sizeof(server_t));

    if (tmp == NULL)
        return tmp;
    tmp->port = -1;
    tmp->resX = -1;
    tmp->resY = -1;
    tmp->tName = NULL;
    tmp->clientNb = -1;
    tmp->freq = 100;
    tmp->verbose = false;
    tmp->client = calloc(1, sizeof(list_t));
    tmp->teams = calloc(1, sizeof(list_t));
    tmp->map = NULL;
    tmp->winner = NULL;
    return tmp;
}

int get_team_nb(const server_t *serv)
{
    int index = 0;

    for (index = 0; serv->tName[index] != NULL;)
        index++;
    return index;
}

void destroy_team(team_t *team)
{
    egg_t *tmp_eggs = NULL;
    size_t size = 0;

    if (team == NULL)
        return;
    if (team->name != NULL)
        free(team->name);
    size = list_get_size(team->eggs);
    for (size_t i = 0; i != size; i++) {
        tmp_eggs = list_get_elem_at_position(team->eggs, i);
        if (tmp_eggs != NULL)
            free(tmp_eggs);
    }
    list_clear(&team->eggs);
    if (team->eggs != NULL)
        free(team->eggs);
    free(team);
}

static void free_struct(server_t *serv)
{
    if (serv == NULL)
        return;
    if (serv->tName != NULL) {
        for (int i = 0; serv->tName[i] != NULL; i++)
            free(serv->tName[i]);
        free(serv->tName);
    }
    list_clear(&serv->client);
    list_clear(&serv->teams);
    if (serv->map != NULL)
        free_map(serv);
    free(serv);
}

static void del_clients(server_t *serv)
{
    size_t clients_nb = list_get_size(serv->client);
    client_t *client = NULL;

    for (size_t i = 0; i != clients_nb; i++) {
        client = list_get_elem_at_position(serv->client, i);
        if (client == NULL)
            continue;
        destroy_client(serv, client);
        list_del_elem_at_position(&serv->client, i);
        i--;
    }
}

void destroy_server(server_t *serv)
{
    team_t *team = NULL;
    size_t team_nb = list_get_size(serv->teams);

    server_log(serv, INFO, 0, "Stopping server...");
    close(serv->socket);
    del_clients(serv);
    for (size_t i = 0; i != team_nb; i++) {
        team = list_get_elem_at_position(serv->teams, i);
        if (team == NULL)
            continue;
        destroy_team(team);
    }
    free_struct(serv);
}
