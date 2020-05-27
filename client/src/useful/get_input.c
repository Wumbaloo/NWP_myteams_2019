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
    char *buffer = NULL;

    if ((*input))
        free(*input);
    if (getline(&buffer, &len, stdin) == -1)
        return (84);
    (*input) = clean_string(buffer);
    free(buffer);
    return (0);
}

int count_occurences_letter(char *input, char separator)
{
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == separator)
            count++;
    }
    return (count);
}
