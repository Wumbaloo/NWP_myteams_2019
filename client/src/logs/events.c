/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Events trigger are in this file
*/

#include "client.h"
#include "logging_client.h"

int create_channel_event_trigger(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_event_channel_created(array[1], array[2], array[3]);
    return (0);
}