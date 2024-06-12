/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** time_management
*/

#include "server.h"
#include <stdlib.h>
#include <sys/time.h>

bool time_is_ready(double time_ready)
{
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    return (time_ready < timeval_get_milliseconds(&current_time));
}

double timeval_get_milliseconds(const struct timeval *tv)
{
    return (tv->tv_sec) * 1000.0 + (tv->tv_usec) / 1000.0;
}
