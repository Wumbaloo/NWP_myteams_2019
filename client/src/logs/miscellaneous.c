/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Miscellaneous triggers
*/

#include "client.h"
#include "logging_client.h"

int user_join_team_trigger(char **array)
{
    if (get_array_length(array) != 3)
        return (0);
    client_print_subscribed(array[1], array[2]);
    return (0);
}

int unsubscribe_trigger(char **array)
{
    if (get_array_length(array) != 3)
        return (0);
    client_print_unsubscribed(array[1], array[2]);
    return (0);
}