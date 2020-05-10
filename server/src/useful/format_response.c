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

char *format_response(int nbr,  ...)
{
    va_list list;
    char *answer = NULL;
    unsigned long size = 0;
    char *buffer = NULL;

    va_start(list, nbr);
    for (int i = 0; i < nbr; i++) {
        buffer = va_arg(list, char *);
        if (!buffer)
            break;
        else if (answer)
            answer[size++] = ' ';
        size += strlen(buffer);
        answer = realloc(answer, sizeof(char) * (size + (i < nbr - 1 ? 2 : 1)));
        if (!answer)
            perror_exit("realloc", 84);
        else
            memcpy(answer + size - strlen(buffer), buffer, strlen(buffer) + 1);
    }
    va_end(list);
    return (answer);
}