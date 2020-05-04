/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Fill logs functions and head
*/

#include <stdio.h>
#include "logging_client.h"
#include "client.h"
#include "logs.h"

int login_trigger(char **array)
{
    if (get_array_length(array) < 2)
        return (1);
    client_event_loggedin(array[1], array[2]);
    return (0);
}

int logout_trigger(char **array)
{
    if (get_array_length(array) < 2)
        return (1);
    client_event_loggedout(array[1], array[2]);
    return (1);
}

void fill_commands(log_t **head)
{
    create_log(head, 230, &login_trigger);
    create_log(head, 231, &logout_trigger);
}