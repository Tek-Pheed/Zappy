/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map
*/

#include <stdlib.h>
#include <time.h>
#include "server.h"

void create_cell(cell_t *cell)
{
    cell->is_player_on = false;
    cell->food = 0;
    cell->stone[linemate] = 0;
    cell->stone[deraumere] = 0;
    cell->stone[sibur] = 0;
    cell->stone[mendiane] = 0;
    cell->stone[phiras] = 0;
    cell->stone[thystame] = 0;
}

cell_t **create_map(server_t *serv)
{
    cell_t **map = calloc(serv->resX, sizeof(cell_t));
    // float food_density = serv->resX * serv->resY * food_r;

    if (map == NULL)
        return NULL;
    srand(time(NULL));
    for (int i = 0; i != serv->resX; i++) {
        map[i] = calloc(serv->resY, sizeof(cell_t));
        for (int y = 0; y != serv->resY; y++) {
            create_cell(&map[i][y]);
        }
    }
    return map;
}
