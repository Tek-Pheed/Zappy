/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#pragma once
#include <sys/time.h>
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
#define DEFAULT_BUFFER_SIZE   25
#include "list.h"

typedef struct cell_s cell_t;
typedef struct server_s server_t;
typedef struct player_s player_t;
typedef struct client_s client_t;
typedef struct team_s team_t;
typedef struct egg_s egg_t;

struct player_s {
    char team_name[BUFFER_MAX_SIZE];
    int x;
    int y;
    int food;
    int stone[6];
    int level;
    int orient;
    int number;
    bool elevating;
};

struct server_s {
    int port;
    int resX;
    int resY;
    char **tName;
    int clientNb;
    int freq;
    int socket;
    list_t *client;
    cell_t **map;
    list_t *teams;
    char *winner;
};

server_t *init_struct(void);
void parse_team_name(server_t *serv, int flags[6], int argc, char *argv[]);
void parse_client_nb(server_t *serv, int flags[6]);
void parse_res_y(server_t *serv, int flags[6]);
void parse_res_x(server_t *serv, int flags[6]);
void parse_port(server_t *serv, int flags[6]);
void free_struct(server_t *serv);
// clang-format off
enum client_state {
    CREATED,
    AI,
    GRAPHICAL
};
// clang-format on
struct client_s {
    int fd;
    char write_buffer[BUFFER_MAX_SIZE];
    char read_buffer[BUFFER_MAX_SIZE];
    char team_name[BUFFER_MAX_SIZE];
    enum client_state state;
    player_t player;
    list_t *cmds;
    struct timeval last_cmd_time;
    int cmd_duration;
};

int server_loop(server_t *serv);
struct cell_s {
    int food;
    int stone[6];
    int nb_player_on;
};
cell_t **create_map(server_t *serv);
void free_map(server_t *serv);
int run_server(server_t *serv);

char *map_size(server_t *serv);

char *tile_content(server_t *serv, int x, int y);

char *all_content(server_t *serv);

char *all_name(server_t *serv);

char *player_position(server_t *serv, int p_index);

char *player_level(server_t *serv, int p_index);

char *player_inventory(server_t *serv, int p_index);

char *conn_new_player(server_t *serv);
int get_team_nb(server_t *serv);

void server_send_data(client_t *client, const char *data);

struct team_s {
    char *name;
    int nb_player;
    list_t *eggs;
};
team_t *get_team_client(server_t *serv, client_t *cli);
int get_free_space_team(team_t *team);

struct egg_s {
    int x;
    int y;
    team_t *team;
};

void run_client_commands(server_t *serv);
char *time_unit_request(server_t *serv);
char *time_unit_modif(server_t *serv, int freq);
char *ressource_drop(int p_index, int r_nb);
char *ressource_collect(int p_index, int r_nb);
char *egg_laying(int p_index);
char *egg_laid(int egg_nb, int p_index, int x, int y);
char *egg_death(int egg_nb);
char *expulsion(int p_index);
char *broadcast(int p_index, char *msg);
char *end_incantation(int x, int y, char *result);
char *player_death(int p_index);
char *player_connection_egg(int p_index);
char *end_game(char *winner);
char *server_message(char *msg);
char *unknow_command(void);
char *command_parameter(void);
char *time_unit_request(server_t *serv);
char *time_unit_modif(server_t *serv, int freq);
char *start_incantation(player_t *player, int *p_nb, int size);
void destroy_server(server_t *serv);
