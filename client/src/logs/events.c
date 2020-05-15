/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Events trigger are in this file
*/

#include <stdlib.h>
#include "client.h"
#include "logging_client.h"

int create_channel_event_trigger(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_event_channel_created(array[1], array[2], array[3]);
    return (0);
}

int create_team_event_trigger(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_event_team_created(array[1], array[2], array[3]);
    return (0);
}

int create_thread_event_trigger(char **array)
{
    long int timestamp;
    char *endptr = NULL;

    if (get_array_length(array) != 5)
        return (0);
    timestamp = strtol(array[3], &endptr, 10);
    client_event_thread_created(array[1], array[2], (time_t) timestamp,
        array[4], array[5]);
    return (0);
}

int create_reply_event_trigger(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_event_thread_message_received(array[1], array[2], array[3],
        array[4]);
    return (0);
}