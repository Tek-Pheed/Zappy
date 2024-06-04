/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** item_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

char *event_ressource_drop(int p_index, int r_nb)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "pdr #%d %d\n", p_index, r_nb);
    return buff;
}

char *event_ressource_collect(int p_index, int r_nb)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "pgt #%d %d\n", p_index, r_nb);
    return buff;
}

char *event_egg_laying(int p_index)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "pfk #%d\n", p_index);
    return buff;
}

char *event_egg_laid(int egg_nb, int p_index, int x, int y)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "enw #%d #%d %d %d\n", egg_nb, p_index, x, y);
    return buff;
}

char *event_egg_death(int egg_nb)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "edi #%d\n", egg_nb);
    return buff;
}
