/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <zconf.h>
#include <string.h>
#include <stdlib.h>
#include "macros.h"

char *format_response(int nbr,  ...)
{
    va_list list;
    char *response = malloc(sizeof(char) * RESPONSE_SIZE);
    unsigned long size = 0;
    char *buffer = NULL;

    memset(response, 0, RESPONSE_SIZE   );
    va_start(list, nbr);
    for (int cpt = 0; cpt < nbr; cpt++) {
        buffer = va_arg(list, char *);
        size = strlen(response) + strlen(buffer);
        strcat(response, buffer);
        response[size] = ' ';
    }
    va_end(list);
    return response;
}