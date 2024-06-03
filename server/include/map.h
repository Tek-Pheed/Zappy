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
};

cell_t **create_map(server_t *serv);
void free_map(server_t *serv);
char *map_size(server_t *serv);
void create_teams_eggs(server_t *serv);
