/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Unknown trigger handler
*/

#include <stdio.h>
#include "client.h"
#include "logging_client.h"

int unknown_team_trigger(char **array)
{
    if (get_array_length(array) != 2)
        return (0);
    client_error_unknown_team(array[1]);
    return (0);
}

int unknown_channel_trigger(char **array)
{
    if (get_array_length(array) != 2)
        return (0);
    client_error_unknown_channel(array[1]);
    return (0);
}

int unknown_thread_trigger(char **array)
{
    if (get_array_length(array) != 2)
        return (0);
    client_error_unknown_thread(array[1]);
    return (0);
}

int unknown_user_trigger(char **array)
{
    if (get_array_length(array) != 2)
        return (0);
    client_error_unknown_user(array[1]);
    return (0);
}