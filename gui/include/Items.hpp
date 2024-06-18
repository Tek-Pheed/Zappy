/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IItems
*/

#pragma once
#include <raylib.h>

namespace Zappy
{
    enum items {
        food = 0,
        linemate = 1,
        deraumere = 2,
        sibur = 3,
        mendiane = 4,
        phiras = 5,
        thystame = 6,
        ITEM_MAX
    };
    constexpr const char *itemNames[] = {"food", "linemate", "deraumere",
        "sibur", "mendiane", "phiras", "thystame"};
} // namespace Zappy
