/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Commands parsing with ""
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    fill_words(array, input, separator, 0);
    return (array);
}