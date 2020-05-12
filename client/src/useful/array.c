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
