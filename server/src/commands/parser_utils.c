/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Parser useful functions
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int char_array_length(char **array)
{
    int len = 0;

    if (!array)
        return (0);
    for (; array[len]; len++);
    return (len);
}

int count_words(char *input, char separator)
{
    int len = strlen(input);
    int nb_args = 0;

    if (input[0] == '/')
        nb_args++;
    for (int index = 0; (index + 1) < len; index++) {
        if (input[index] == separator && input[index + 1] != separator) {
            for (; index < len && input[index] == separator; index++);
            index++;
            nb_args++;
        }
    }
    return (nb_args);
}

int is_banned_char(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}