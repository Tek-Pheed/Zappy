/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_comm
*/

#pragma once
#include "server.h"

char *to_lower_case(const char *str);
bool ai_take_object(server_t *serv, client_t *cli, const char *obj);
bool ai_set_object(server_t *serv, client_t *cli, const char *obj);
bool ai_move_forward(
    UNUSED server_t *serv, client_t *cli, UNUSED const char *obj);
bool ai_turn_right(
    UNUSED server_t *serv, client_t *cli, UNUSED const char *obj);
bool ai_turn_left(
    UNUSED server_t *serv, client_t *cli, UNUSED const char *obj);
bool ai_inventory(
    UNUSED server_t *serv, client_t *cli, UNUSED const char *obj);
bool ai_dead(UNUSED server_t *serv, client_t *cli, UNUSED const char *obj);
bool ai_connect_nbr(
    UNUSED server_t *serv, client_t *cli, UNUSED const char *obj);
