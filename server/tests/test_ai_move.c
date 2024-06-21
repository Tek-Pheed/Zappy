/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_ai_move
*/

#include <dlfcn.h>
#include <unistd.h>
#include <criterion/criterion.h>
#include "client.h"
#include "define.h"

static bool ai_move_forward(client_t *cli)
{
    if (cli->player.orient == NORTH)
        cli->player.y = cli->player.y == 0 ? TEST_MAPY - 1 : cli->player.y - 1;
    if (cli->player.orient == SOUTH)
        cli->player.y = cli->player.y == TEST_MAPY - 1 ? 0 : cli->player.y + 1;
    if (cli->player.orient == EAST)
        cli->player.x = cli->player.x == TEST_MAPX - 1 ? 0 : cli->player.x + 1;
    if (cli->player.orient == WEST)
        cli->player.x = cli->player.x == 0 ? TEST_MAPX - 1 : cli->player.x - 1;
    return true;
}

static client_t *create_client(int x, int y, int orient)
{
    client_t *tmp = calloc(1, sizeof(client_t));

    tmp->player.food = 10;
    tmp->player.elevating = -1;
    tmp->player.level = 1;
    tmp->player.orient = orient;
    tmp->player.x = x;
    tmp->player.y = y;
    return tmp;
}

Test(ai_forward, test_move_forward_north)
{
    client_t *cli = create_client(5, 5, NORTH);

    ai_move_forward(cli);
    cr_assert(cli->player.x == 5);
    cr_assert(cli->player.y == 4);
    free(cli);
}

Test(ai_forward, test_move_forward_east)
{
    client_t *cli = create_client(5, 5, EAST);

    ai_move_forward(cli);
    cr_assert(cli->player.x == 6);
    cr_assert(cli->player.y == 5);
    free(cli);
}

Test(ai_forward, test_move_forward_south)
{
    client_t *cli = create_client(5, 5, SOUTH);

    ai_move_forward(cli);
    cr_assert(cli->player.x == 5);
    cr_assert(cli->player.y == 6);
    free(cli);
}

Test(ai_forward, test_move_forward_west)
{
    client_t *cli = create_client(5, 5, WEST);

    ai_move_forward(cli);
    cr_assert(cli->player.x == 4);
    cr_assert(cli->player.y == 5);
    free(cli);
}
