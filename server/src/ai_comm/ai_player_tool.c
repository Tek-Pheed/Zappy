/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_player_tool
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "server.h"

bool ai_inventory(UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    char *buff = calloc(BUFFER_MAX_SIZE, sizeof(char));

    if (!buff)
        return false;
    sprintf(buff,
        "linemate %d, deraumere %d, sibur %d, mendiane %d, phiras %d, "
        "thystame %d, food %d\n",
        cli->player->stone[LINEMATE], cli->player->stone[DERAUMERE],
        cli->player->stone[SIBUR], cli->player->stone[MENDIANE],
        cli->player->stone[PHIRAS], cli->player->stone[THYSTAME],
        cli->player->food);
    cli->cmd_duration = 1;
    gettimeofday(&cli->last_cmd_time, NULL);
    server_send_data(cli, buff);
    free(buff);
    return true;
}

bool ai_dead(UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    server_send_data(cli, "dead\n");
    return true;
}

bool ai_connect_nbr(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    int value = get_free_space_team(get_team_client(serv, cli));
    char str[12];

    memset(str, '\0', sizeof(str));
    if (value >= 0) {
        sprintf(str, "%d\n", value);
        server_send_data(cli, str);
    }
    return true;
}

bool ai_fork(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    team_t *tmp = get_team_client(serv, cli);
    egg_t *egg = NULL;

    if (tmp == NULL)
        return false;
    egg = calloc(1, sizeof(egg_t));
    egg->team = tmp;
    egg->x = cli->player->x;
    egg->y = cli->player->y;
    cli->cmd_duration = 42;
    list_add_elem_at_back(&tmp->eggs, egg);
    gettimeofday(&cli->last_cmd_time, NULL);
    server_send_data(cli, "ok\n");
    return true;
}

static void eject_destroy_eggs(client_t *cli, team_t *tmp_team, int i, int y)
{
    egg_t *tmp_eggs = NULL;

    tmp_eggs = list_get_elem_at_position(tmp_team->eggs, i);
    if (tmp_eggs->x == cli->player->x && tmp_eggs->y == cli->player->y) {
        free(list_get_elem_at_position(tmp_team->eggs, y));
        list_del_elem_at_position(&tmp_team->eggs, y);
    }
}

static void eject_player(int i, client_t *cli, server_t *serv, char msg[20])
{
    client_t *tcli = NULL;

    tcli = list_get_elem_at_position(serv->client, i);
    if (tcli->player->x == cli->player->x && tcli->player->y == cli->player->y)
        server_send_data(tcli, msg);
}

bool ai_eject(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    int len_client = list_get_size(serv->client);
    int len_team = list_get_size(serv->teams);
    int len_eggs = 0;
    team_t *tteam = NULL;
    char msg[20];

    memset(msg, '\0', sizeof(msg));
    sprintf(msg, "eject: %d\n", cli->player->orient);
    for (int i = 0; i != len_client; i++)
        eject_player(i, cli, serv, msg);
    for (int i = 0; i != len_team; i++) {
        tteam = list_get_elem_at_position(serv->teams, i);
        len_eggs = list_get_size(tteam->eggs);
        for (int y = 0; y != len_eggs; y++) {
            eject_destroy_eggs(cli, tteam, i, y);
        }
    }
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    return true;
}
