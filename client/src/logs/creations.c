/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Creations trigger (like /create teams)
*/

#include <stdlib.h>
#include "client.h"
#include "logging_client.h"

int create_team_specific_trigger(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_print_team_created(array[1], array[2], array[3]);
    return (0);
}

int create_channel_specific_trigger(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_print_channel_created(array[1], array[2], array[3]);
    return (0);
}

int create_thread_specific_trigger(char **array)
{
    long int timestamp;
    char *endptr = NULL;

    if (get_array_length(array) != 6)
        return (0);
    timestamp = strtol(array[3], &endptr, 10);
    client_print_thread_created(array[1], array[2], (time_t) timestamp,
        array[4], array[5]);
    return (0);
}

int create_reply_specific_trigger(char **array)
{
    long int timestamp;
    char *endptr = NULL;

    if (get_array_length(array) != 5)
        return (0);
    timestamp = strtol(array[3], &endptr, 10);
    client_print_reply_created(array[1], array[2], (time_t) timestamp,
        array[4]);
    return (0);
}
