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

void distribute_items_after(
    cell_t **map, const server_t *serv, int quant, int item_type)
{
    int x = 0;
    int y = 0;

    srand(time(NULL));
    for (int i = 0; i < quant; ++i) {
        x = rand() % serv->resX;
        y = rand() % serv->resY;
        if (item_type == 6) {
            map[x][y].food++;
            event_tile_update(serv, x, y);
        } else {
            map[x][y].stone[item_type]++;
            event_tile_update(serv, x, y);
        }
    }
}
