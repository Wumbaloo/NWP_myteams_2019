/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Users related trigger
*/

#include <stdlib.h>
#include <stdio.h>
#include "logging_client.h"
#include "client.h"

int list_private_messages_trigger(char **array)
{
    long int timestamp;
    char *endptr = NULL;

    if (get_array_length(array) != 4)
        return (0);
    timestamp = strtol(array[2], &endptr, 10);
    client_private_message_print_messages(array[1], (time_t) timestamp,
        array[3]);
    return (0);
}

int private_message_trigger(char **array)
{
    if (get_array_length(array) != 3)
        return (0);
    client_event_private_message_received(array[1], array[2]);
    return (0);
}

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

int already_exists_trigger(char **array)
{
    (void)(array);
    client_error_already_exist();
    return 0;
}