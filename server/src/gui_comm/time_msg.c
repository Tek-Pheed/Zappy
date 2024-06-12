/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** time_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

char *time_unit_request(const server_t *serv)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "sgt %d\n", serv->freq);
    return buff;
}

char *time_unit_modif(server_t *serv, int freq)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if (!buff)
        return NULL;
    serv->freq = freq;
    sprintf(buff, "sst %d\n", serv->freq);
    return buff;
}
