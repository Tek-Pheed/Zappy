/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

char *end_game(char *winner)
{
    char *buff = calloc(DEFAULT_BUFFER_SIZE * 2, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "seg %s\n", winner);
    return buff;
}

char *server_message(char *msg)
{
    char *buff = calloc(strlen(msg) + 5, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "smg %s\n", msg);
    return buff;
}

char *unknow_command(void)
{
    char *buff = calloc(5, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "suc\n");
    return buff;
}

char *command_parameter(void)
{
    char *buff = calloc(5, sizeof(char));

    if (!buff)
        return NULL;
    sprintf(buff, "sbp\n");
    return buff;
}