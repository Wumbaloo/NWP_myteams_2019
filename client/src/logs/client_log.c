/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Log about clients trigger
*/

#include <stdlib.h>
#include <stdio.h>
#include "logging_client.h"
#include "client.h"

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

int already_logged_in_trigger(char **array)
{
    printf("Client already logged in.\r\n");
    return (1);
}