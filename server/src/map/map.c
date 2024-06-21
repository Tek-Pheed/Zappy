/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map
*/

#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "server.h"

void calculate_quantity(const server_t *serv, float quantity[7])
{
    float total = serv->resX * serv->resY;

    quantity[LINEMATE] = (total * LINEMATE_R);
    quantity[DERAUMERE] = (total * DERAUMERE_R);
    quantity[SIBUR] = (total * SIBUR_R);
    quantity[MENDIANE] = (total * MENDIANE_R);
    quantity[PHIRAS] = (total * PHIRAS_R);
    quantity[THYSTAME] = (total * THYSTAME_R);
    quantity[6] = (total * FOOD_R);
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

static void shuffle_cell(int totalCells, int *cellIn)
{
    int j = 0;
    int tmp = 0;

    for (int i = totalCells - 1; i > 0; --i) {
        j = rand() % (i + 1);
        tmp = cellIn[i];
        cellIn[i] = cellIn[j];
        cellIn[j] = tmp;
    }
}

void distribute_items(
    cell_t **map, const server_t *serv, int quant, int item_type)
{
    int totalCells = serv->resX * serv->resY;
    int *cellIn = malloc(totalCells * sizeof(int));

    srand(time(NULL));
    if (cellIn == NULL)
        return;
    for (int i = 0; i < totalCells; ++i)
        cellIn[i] = i;
    shuffle_cell(totalCells, cellIn);
    for (int i = 0; i < quant; ++i) {
        if (item_type == 6)
            map[cellIn[i] % serv->resX][cellIn[i] / serv->resX].food++;
        else
            map[cellIn[i] % serv->resX][cellIn[i] / serv->resX]
                .stone[item_type]++;
    }
    free(cellIn);
}

void free_map(server_t *serv)
{
    for (int i = 0; i < serv->resX; ++i) {
        free(serv->map[i]);
    }
    free(serv->map);
    serv->map = NULL;
}

cell_t **create_map(const server_t *serv)
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
