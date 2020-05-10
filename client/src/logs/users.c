/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Users related trigger
*/

#include <stdlib.h>
#include "logging_client.h"
#include "client.h"

int users_list_trigger(char **array)
{
    char *endptr = NULL;
    long int status = -1;

    if (get_array_length(array) != 4)
        return (0);
    status = strtol(array[3], &endptr, 10);
    client_print_users(array[1], array[2], status);
    return (0);
}

int unknown_user_trigger(char **array)
{
    if (get_array_length(array) != 2)
        return (0);
    client_error_unknown_user(array[1]);
    return (0);
}

int specific_user_trigger(char **array)
{
    char *endptr = NULL;
    long int status = -1;

    if (get_array_length(array) != 4)
        return (0);
    status = strtol(array[3], &endptr, 10);
    client_print_user(array[1], array[2], status);
    return (0);
}