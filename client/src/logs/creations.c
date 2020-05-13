/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Creations trigger (like /create teams)
*/

#include "client.h"
#include "logging_client.h"

int create_team_specific_trigger(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_print_team_created(array[1], array[2], array[3]);
    return (0);
}

int create_team_trigger(char **array)
{
    if (get_array_length(array) != 4)
        return (0);
    client_event_team_created(array[1], array[2], array[3]);
    return (0);
}