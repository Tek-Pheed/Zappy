/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** update_map
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "commands.h"
#include "map.h"
#include "server.h"

static void get_current_quantity(const server_t *serv, float quantity[7])
{
    for (int i = 0; i != serv->resX; i++) {
        for (int j = 0; j != serv->resY; j++) {
            quantity[LINEMATE] += serv->map[i][j].stone[LINEMATE];
            quantity[DERAUMERE] += serv->map[i][j].stone[DERAUMERE];
            quantity[SIBUR] += serv->map[i][j].stone[SIBUR];
            quantity[MENDIANE] += serv->map[i][j].stone[MENDIANE];
            quantity[PHIRAS] += serv->map[i][j].stone[PHIRAS];
            quantity[THYSTAME] += serv->map[i][j].stone[THYSTAME];
            quantity[6] += serv->map[i][j].food;
        }
    }
}

void calculate_quantity_after(const server_t *serv, float *quantity)
{
    float total = serv->resX * serv->resY;

    get_current_quantity(serv, quantity);
    quantity[LINEMATE] = (total * LINEMATE_R) - quantity[LINEMATE];
    quantity[DERAUMERE] = (total * DERAUMERE_R) - quantity[DERAUMERE];
    quantity[SIBUR] = (total * SIBUR_R) - quantity[SIBUR];
    quantity[MENDIANE] = (total * MENDIANE_R) - quantity[MENDIANE];
    quantity[PHIRAS] = (total * PHIRAS_R) - quantity[PHIRAS];
    quantity[THYSTAME] = (total * THYSTAME_R) - quantity[THYSTAME];
    quantity[6] = (total * FOOD_R) - quantity[6];
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

void distribute_items_after(
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
        if (item_type == 6) {
            map[cellIn[i] % serv->resX][cellIn[i] / serv->resX].food++;
            server_log(serv, INFO, 0, "Adding food on map");
        } else {
            map[cellIn[i] % serv->resX][cellIn[i] / serv->resX]
                .stone[item_type]++;
            server_log(serv, INFO, 0, "Adding stone on map");
        }
    }
    free(cellIn);
}
