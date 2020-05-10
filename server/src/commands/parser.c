/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Commands parsing with ""
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "prototypes.h"

int copy_cmd(char **array, char *input, char separator)
{
    int len = strlen(input);
    int cmd_i = 0;

    for (int i = 0; (i + 1) < len; i++) {
        if (input[i] != separator && input[i + 1] == separator) {
            cmd_i = i;
            break;
        }
    }
    if (cmd_i == 0)
        for (; input[cmd_i] != '\0' && !is_banned_char(input[cmd_i]); cmd_i++);
    array[0] = malloc(sizeof(char) * (cmd_i + 1));
    if (!array[0])
        return (-1);
    strncpy(array[0], input, cmd_i);
    array[0][cmd_i] = '\0';
    return (cmd_i);
}

int fill_words(char **array, char *input, char separator, int from)
{
    int y = 1;
    int copy = 0;

    for (int i = from; input[i] != '\0'; i++) {
        if (input[i] == separator && input[i + 1] != separator && !copy) {
            for (; input[i] && (is_banned_char(input[i]) ||
                (input[i] == separator && input[i + 1] == separator)); i++);
            from = i + 1;
            copy = 1;
        } else if (input[i] == separator && copy) {
            array[y] = malloc(sizeof(char) * ((i - from) + 1));
            if (array[y] == NULL)
                return (1);
            array[y] = strncpy(array[y], input + from, (i - from));
            array[y++][i - from] = '\0';
            copy = 0;
            for (; input[i] && (is_banned_char(input[i]) ||
                (input[i] == separator && input[i + 1] == separator)); i++);
        }
    }
    return (0);
}

int fill_array(char **array, char *input, char separator)
{
    int from = copy_cmd(array, input, separator);

    if (from < 0)
        return (1);
    else if (!fill_words(array, input, separator, from))
        return (1);
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

char **parse_arguments(char *input, char separator)
{
    char **array = NULL;
    int nb_args = 0;

    if (!input)
        return (NULL);
    else if (count_occurences_letter(input, separator) % 2 != 0)
        return (NULL);
    nb_args = count_words(input, separator);
    array = malloc(sizeof(char *) * (nb_args + 1));
    if (!array)
        return (NULL);
    array[nb_args] = NULL;
    fill_array(array, input, separator);
    return (array);
}