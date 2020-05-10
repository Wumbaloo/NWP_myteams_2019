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

void fill_errors(log_t **head)
{
    create_log(head, 601, &bad_cmd_trigger);
    create_log(head, 602, &bad_params_trigger);
}

void fill_commands(log_t **head)
{
    create_log(head, 42, &login_trigger);
    create_log(head, 84, &logout_trigger);
    create_log(head, 645, &unauthorized_trigger);
    create_log(head, 730, &users_list_trigger);
    create_log(head, 740, &specific_user_trigger);
    create_log(head, 635, &unknown_user_trigger);
    fill_errors(head);
}