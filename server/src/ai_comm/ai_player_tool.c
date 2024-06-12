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
#include "commands.h"
#include "define.h"
#include "server.h"

bool ai_inventory(UNUSED server_t *serv, client_t *cli, UNUSED const char *obj)
{
    char *buff = calloc(BUFFER_MAX_SIZE, sizeof(char));

    if (!buff)
        return false;
    sprintf(buff,
        "[ food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, phiras "
        "%d, "
        "thystame %d ]\n",
        cli->player.food, cli->player.stone[LINEMATE],
        cli->player.stone[DERAUMERE], cli->player.stone[SIBUR],
        cli->player.stone[MENDIANE], cli->player.stone[PHIRAS],
        cli->player.stone[THYSTAME]);
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
    int value = team_get_free_space(team_get_client(serv, cli));
    char str[12];

    memset(str, '\0', sizeof(str));
    if (value >= 0) {
        sprintf(str, "%d\n", value);
        server_send_data(cli, str);
    }
    return true;
}

static void eject_destroy_eggs(const server_t *serv, const client_t *cli,
    team_t *tmp_team, const ivect2D_t *iy)
{
    egg_t *tmp_eggs = NULL;

    tmp_eggs = list_get_elem_at_position(tmp_team->eggs, iy->x);
    if (tmp_eggs == NULL)
        return;
    event_egg_death(serv, cli, tmp_eggs->number);
    if (tmp_eggs->x == cli->player.x && tmp_eggs->y == cli->player.y) {
        tmp_eggs = list_get_elem_at_position(tmp_team->eggs, iy->y);
        if (tmp_eggs == NULL)
            return;
        free(tmp_eggs);
        list_del_elem_at_position(&tmp_team->eggs, iy->y);
    }
}

static void eject_player(
    int i, const client_t *cli, server_t *serv, const char msg[20])
{
    client_t *tcli = NULL;

    tcli = list_get_elem_at_position(serv->client, i);
    if (tcli != NULL && tcli->player.x == cli->player.x
        && tcli->player.y == cli->player.y) {
        server_send_data(tcli, msg);
        event_expulsion(serv, cli);
    }
}

static void sub_eject(server_t *serv, client_t *cli)
{
    char msg[20];
    int len_client = list_get_size(serv->client);

    memset(msg, '\0', sizeof(msg));
    sprintf(msg, "eject: %d\n", cli->player.orient);
    for (int i = 0; i != len_client; i++)
        eject_player(i, cli, serv, msg);
}

bool ai_eject(server_t *serv, client_t *cli, UNUSED const char *obj)
{
    int len_team = list_get_size(serv->teams);
    int len_eggs = 0;
    team_t *tteam = NULL;

    sub_eject(serv, cli);
    for (int i = 0; i != len_team; i++) {
        tteam = list_get_elem_at_position(serv->teams, i);
        if (tteam == NULL)
            continue;
        len_eggs = list_get_size(tteam->eggs);
        for (int y = 0; y != len_eggs; y++)
            eject_destroy_eggs(serv, cli, tteam, &((ivect2D_t){i, y}));
    }
    cli->cmd_duration = 7;
    gettimeofday(&cli->last_cmd_time, NULL);
    return true;
}
