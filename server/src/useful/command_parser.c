/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** command_parser.c
*/

#include <stdio.h>
#include <string.h>
#include "prototypes.h"

int parse_quote(int start, char *input)
{
    int open = 0;

    for (int i = start; i < strlen(input); i++) {
        if (!open) {
            if (input[i] != ' ' && input[i] != '"')
                return (-1);
        }
        if (!open && input[i] == '"') {
            open = 1;
            continue;
        }
        if (open && input[i] == '"') {
            open = 0;
            if (i < strlen(input) - 1)
                return (-1);
        }
    }
    return (0);
}

int command_parser(char *input, myteams_t *teams, client_t *client)
{
    int start = 0;

    if (input[0] != '/')
        return (-1);
    for (; input[start] != ' '; start++);
    start++;
    return (parse_quote(start, input));
}