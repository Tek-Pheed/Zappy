/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** gui_update
*/

#include <stdlib.h>
#include "commands.h"
#include "define.h"
#include "server.h"

void event_update_map(server_t *serv)
{
    char *buff = all_content(serv);

    if (buff == NULL)
        return;
    server_event_send_many(serv, GRAPHICAL, buff);
    free(buff);
}

void event_time_modif(server_t *serv)
{
    char *buff = time_unit_modif(serv, serv->freq);

    if (buff == NULL)
        return;
    server_event_send_many(serv, GRAPHICAL, buff);
    free(buff);
}
