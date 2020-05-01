/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Exit correctly and with perror
*/

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void free_all(myteams_t *teams)
{
    (void)(teams);
}

void perror_exit(char *err, int exit_code)
{
    perror(err);
    exit(exit_code);
}