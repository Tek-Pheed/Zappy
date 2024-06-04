/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "server.h"

void calculate_quantity(server_t *serv, float quantity[7])
{
    float total = serv->resX * serv->resY;

    quantity[LINEMATE] = total * LINEMATE_R;
    quantity[DERAUMERE] = total * DERAUMERE_R;
    quantity[SIBUR] = total * SIBUR_R;
    quantity[MENDIANE] = total * MENDIANE_R;
    quantity[PHIRAS] = total * PHIRAS_R;
    quantity[THYSTAME] = total * THYSTAME_R;
    quantity[6] = total * FOOD_R;
}

static void create_cell(cell_t *cell, int x, int y)
{
    cell->nb_player_on = 0;
    cell->food = 0;
    cell->x = x;
    cell->y = y;
    for (int i = 0; i < 6; ++i)
        cell->stone[i] = 0;
}

void distribute_items(cell_t **map, server_t *serv, int quant, int item_type)
{
    int x = 0;
    int y = 0;

    srand(time(NULL));
    for (int i = 0; i < quant; ++i) {
        x = rand() % serv->resX;
        y = rand() % serv->resY;
        if (item_type == 6) {
            map[x][y].food++;
        } else {
            map[x][y].stone[item_type]++;
        }
    }
}

void free_map(server_t *serv)
{
    for (int i = 0; i < serv->resX; ++i) {
        free(serv->map[i]);
    }
    free(serv->map);
    serv->map = NULL;
}

cell_t **create_map(server_t *serv)
{
    cell_t **map = calloc(serv->resX, sizeof(cell_t *));
    float quant[7] = {0};

    if (map == NULL)
        return NULL;
    calculate_quantity(serv, quant);
    for (int i = 0; i != serv->resX; i++) {
        map[i] = calloc(serv->resY, sizeof(cell_t));
        for (int y = 0; y != serv->resY; y++)
            create_cell(&map[i][y], i, y);
    }
    for (int i = 0; i != 7; i++)
        distribute_items(map, serv, quant[i], i);
    return map;
}
