/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** PlayerLevel.hpp
*/

#pragma once
#include <queue>

namespace Zappy {

    class PlayerLevel{
        PlayerLevel();
        ~PlayerLevel();
        std::queue getPlayerLevel();
    };
}