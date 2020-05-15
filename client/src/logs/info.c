/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Info command trigger
*/

#include <stdlib.h>
#include <stdio.h>
#include "logging_client.h"
#include "client.h"

int info_team(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_print_team(array[1], array[2], array[3]);
    return (0);
}

int info_channel(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_print_channel(array[1], array[2], array[3]);
    return (0);
}

int info_thread(char **array)
{
    long int timestamp;
    char *endptr = NULL;

    if (get_array_length(array) != 6)
        return (0);
    timestamp = strtol(array[3], &endptr, 10);
    client_print_thread(array[1], array[2], (time_t) timestamp,
        array[4], array[5]);
    return (0);
}