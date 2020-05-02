/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"

void free_myteams(myteams_t *myteams)
{
    if (myteams->server)
        free(myteams->server);
    if (myteams->clients)
        free(myteams->clients);
    if (myteams->client_head)
        free_clients_list(myteams->client_head);
    if (myteams->team_head)
        free_teams_list(myteams->team_head);
    free(myteams);
}