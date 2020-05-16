/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <zconf.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"
#include "macros.h"

char *put_char_around(char *buffer, char around)
{
    size_t len = snprintf(NULL, 0, "%c%s%c", around, buffer, around);
    char *new_buffer = malloc(sizeof(char) * (len + 1));

    if (!new_buffer)
        perror_exit("malloc", 84);
    sprintf(new_buffer, "%c%s%c", around, buffer, around);
    return (new_buffer);
}

char *format_response(size_t nbr, ...)
{
    va_list list;
    char *answer = NULL;
    char *buffer = NULL;

    va_start(list, nbr);
    for (size_t i = 0, size = 0; i < nbr; i++) {
        buffer = va_arg(list, char *);
        if (!buffer)
            break;
        else if (answer)
            answer[size++] = ' ';
        buffer = put_char_around(buffer, '\"');
        size += strlen(buffer);
        answer = realloc(answer, sizeof(char) * (size + (i < nbr - 1 ? 2 : 1)));
        if (!answer)
            perror_exit("realloc", 84);
        memcpy(answer + size - strlen(buffer), buffer, strlen(buffer) + 1);
        free(buffer);
    }
    va_end(list);
    return (answer);
}