/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Fill logs functions and head
*/

#include <stdio.h>
#include "logs.h"

void print_help(char **array)
{
    printf("HERE HELP COMMAND with %s\n", array[0]);
}

void fill_commands(log_t **head)
{
    create_log(head, 530, &print_help);
}