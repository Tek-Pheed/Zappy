/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_ai_turn
*/

#include <dlfcn.h>
#include <unistd.h>
#include <criterion/criterion.h>
#include "client.h"
#include "define.h"

// clang-format off
static bool ai_turn_right(client_t *cli)
{
    switch (cli->player.orient) {
        case NORTH:
            cli->player.orient = EAST;
            break;
        case EAST:
            cli->player.orient = SOUTH;
            break;
        case SOUTH:
            cli->player.orient = WEST;
            break;
        case WEST:
            cli->player.orient = NORTH;
            break;
        default:
            return false;
    }
    return true;
}
// clang-format on

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

Test(ai_turn, test_turn_right_north)
{
    client_t *cli = create_client(5, 5, NORTH);

    ai_turn_right(cli);
    cr_assert(cli->player.orient == EAST);
    cr_assert(cli->player.x == 5);
    cr_assert(cli->player.y == 5);
    free(cli);
}

Test(ai_turn, test_turn_right_east)
{
    client_t *cli = create_client(5, 5, EAST);

    ai_turn_right(cli);
    cr_assert(cli->player.orient == SOUTH);
    cr_assert(cli->player.x == 5);
    cr_assert(cli->player.y == 5);
    free(cli);
}

Test(ai_turn, test_turn_right_south)
{
    client_t *cli = create_client(5, 5, SOUTH);

    ai_turn_right(cli);
    cr_assert(cli->player.orient == WEST);
    cr_assert(cli->player.x == 5);
    cr_assert(cli->player.y == 5);
    free(cli);
}

Test(ai_turn, test_turn_right_west)
{
    client_t *cli = create_client(5, 5, WEST);

    ai_turn_right(cli);
    cr_assert(cli->player.orient == NORTH);
    cr_assert(cli->player.x == 5);
    cr_assert(cli->player.y == 5);
    free(cli);
}
