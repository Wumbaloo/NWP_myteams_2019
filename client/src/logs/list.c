/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Creations trigger (like /create teams)
*/

#include <stdlib.h>
#include "client.h"
#include "logging_client.h"

int list_teams(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_print_teams(array[1], array[2], array[3]);
    return (0);
}

int list_channels(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_team_print_channels(array[1], array[2], array[3]);
    return (0);
}

int list_threads(char **array)
{
    long int timestamp;
    char *endptr = NULL;

    if (get_array_length(array) != 6)
        return (0);
    timestamp = strtol(array[3], &endptr, 10);
    client_channel_print_threads(array[1], array[2], (time_t) timestamp,
        array[4], array[5]);
    return (0);
}

int list_replies(char **array)
{
    long int timestamp;
    char *endptr = NULL;

    if (get_array_length(array) != 5)
        return (0);
    timestamp = strtol(array[3], &endptr, 10);
    client_thread_print_replies(array[1], array[2], (time_t) timestamp,
        array[4]);
    return (0);
}
