/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map
*/

#pragma once
#include "define.h"
#include "server.h"

struct cell_s {
    int food;
    int stone[6];
    int nb_player_on;
    int x;
    int y;
};

cell_t **create_map(const server_t *serv);
void free_map(server_t *serv);
char *map_size(const server_t *serv);
void create_teams_eggs(server_t *serv);
void distribute_items(
    cell_t **map, const server_t *serv, int quant, int item_type);
void calculate_quantity(const server_t *serv, float quantity[7]);
void calculate_quantity_after(const server_t *serv, float *quantity);
void distribute_items_after(
    cell_t **map, const server_t *serv, int quant, int item_type);
