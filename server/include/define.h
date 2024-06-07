/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** define
*/

#pragma once
#define BUFFER_MAX_SIZE        2048
#define MAX_CONCURENT_COMMANDS 10

#define OFFSET_ARGS           8
#define UNUSED                __attribute__((unused))
#define CONN_TIMEOUT_DELAY_US 25000000
#define LINEMATE              0
#define DERAUMERE             1
#define SIBUR                 2
#define MENDIANE              3
#define PHIRAS                4
#define THYSTAME              5
#define LINEMATE_R            0.3
#define DERAUMERE_R           0.15
#define SIBUR_R               0.1
#define MENDIANE_R            0.1
#define PHIRAS_R              0.08
#define THYSTAME_R            0.05
#define FOOD_R                0.5
#define NORTH                 1
#define EAST                  2
#define SOUTH                 3
#define WEST                  4
#define DEFAULT_BUFFER_SIZE   100
#define TEST_MAPX             10
#define TEST_MAPY             10

typedef struct server_s server_t;
typedef struct cell_s cell_t;
typedef struct client_s client_t;
typedef struct player_s player_t;
typedef struct team_s team_t;
typedef struct egg_s egg_t;
