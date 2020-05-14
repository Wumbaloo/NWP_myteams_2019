/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include "structs.h"
#include "prototypes.h"

int shutdown_cmd(myteams_t *teams, client_t *client, char **input)
{
    (void)(input);
    (void)(client);
    printf("here\n");
    save(teams);
    return (1);
}