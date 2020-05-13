/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Commands parsing with ""
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "client.h"

int count_words(char *input, char separator)
{
    int len = strlen(input);
    int nb_args = 0;

    for (int index = 0; (index + 1) < len; index++) {
        if (input[index] == separator && input[index + 1] != separator) {
            for (; index < len && input[index + 1] != separator; index++);
            index++;
            nb_args++;
        }
    }
    return (nb_args);
}

int is_parser_char(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int fill_words(char **array, char *input, char separator, int from)
{
    int y = 0;
    int copy = 0;

    for (int i = from; input[i] != '\0'; i++) {
        if (input[i] == separator && input[i + 1] != separator && !copy) {
            for (; input[i] && (is_parser_char(input[i]) ||
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
            for (; input[i] && (is_parser_char(input[i]) ||
                (input[i] == separator && input[i + 1] == separator)); i++);
        }
    }
    return (0);
}

void fill_code(char **array, char *input)
{
    size_t len = 0;
    size_t from = 0;

    for (; input[len] && input[len] != ' '; len++);
    array[0] = malloc(sizeof(char) * (len + 1));
    if (!array[0])
        exit(84);
    array[0][len] = '\0';
    for (; input[from] && from < len; from++)
        array[0][from] = input[from];
    len++;
    for (; input[len] && input[len] != ' '; len++);
    from++;
    array[1] = malloc(sizeof(char) * ((len - from) + 1));
    if (!array[1])
        exit(84);
    array[1][len - from] = '\0';
    for (int i = 0; input[from] && from < len; from++)
        array[1][i++] = input[from];
}

char **parse_arguments(char *input, char separator)
{
    char **array = NULL;
    int nb_args = 0;
    int error = count_occurences_letter(input, separator) % 2;

    nb_args = ((error != 0) ? 2 : count_words(input, separator));
    array = malloc(sizeof(char *) * (nb_args + 1));
    if (!array)
        exit(84);
    array[nb_args] = NULL;
    if (error != 0)
        fill_code(array, input);
    else
        fill_words(array, input, separator, 0);
    return (array);
}