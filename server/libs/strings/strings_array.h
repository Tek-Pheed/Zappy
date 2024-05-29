/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** strings
*/

#pragma once

char **str_to_array(const char *buffer, const char *delim, int max_delim);
void str_array_destroy(char **array);
char *get_str_part(
    const char *buffer, const char *delim, int max_delim, int index);
