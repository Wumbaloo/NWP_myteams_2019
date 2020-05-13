/*
** EPITECH PROJECT, 2019
** get_input.c
** File description:
** getline on stdin
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

int get_input(char **input)
{
    size_t len = 0;

    if (*input)
        free(*input);
    if (getline(&(*input), &len, stdin) == -1)
        return (84);
    (*input) = clean_string(*input);
    if (strcmp((*input), "/logout") == 0)
        return (1);
    return (0);
}