/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player_event_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

char *event_expulsion(int p_index)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "pex #%d\n", p_index);
    return buff;
}

char *event_broadcast(int p_index, char *msg)
{
    char *buff = calloc(BUFFER_MAX_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "pbc #%d %s\n", p_index, msg);
    return buff;
}

char *event_end_incantation(int x, int y, char *result)
{
    char *buff = calloc(BUFFER_MAX_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "pie %d %d %s\n", x, y, result);
    return buff;
}

char *event_player_death(int p_index)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "pdi %d\n", p_index);
    return buff;
}

char *event_player_connection_egg(int p_index)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "ebo #%d\n", p_index);
    return buff;
}
