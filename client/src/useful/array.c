/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Array related useful functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_array_length(char **array)
{
    int len = 0;

    if (!array)
        return (0);
    for (; array[len]; len++);
    return (len);
}

char *concat_array(char **array, int begin)
{
    char *msg = NULL;
    int array_length = get_array_length(array);
    int len = 0;

    if (begin >= array_length)
        return (NULL);
    for (int i = begin; i < array_length; i++)
        len += strlen(array[i]);
    len += (array_length - begin);
    msg = malloc(sizeof(char) * (len + 1));
    if (!msg) {
        perror("malloc");
        exit(84);
    }
    memset(msg, 0, len + 1);
    for (int i = begin; i < array_length; i++) {
        strcat(msg, array[i]);
        strcat(msg, (i < array_length - 1 ? " " : "\0"));
    }
    return (msg);
}