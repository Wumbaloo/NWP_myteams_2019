/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Error's trigger handler
*/

#include <stdio.h>
#include "client.h"
#include "logging_client.h"

int return_with_perror(char *msg, int value)
{
    perror(msg);
    return (value);
}

int bad_cmd_trigger(char **array)
{
    if (get_array_length(array) < 2)
        return (1);
    printf("%s: Unknown command.\r\n", array[1]);
    return (0);
}

int bad_params_trigger(char **array)
{
    if (get_array_length(array) < 2)
        return (1);
    printf("%s: Bad parameters.\r\n", array[1]);
    return (0);
}

int unauthorized_trigger(char **array)
{
    (void)(array);
    client_error_unauthorized();
    return (0);
}