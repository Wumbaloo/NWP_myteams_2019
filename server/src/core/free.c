/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Where teams is freed
*/

#include <stdlib.h>
#include <unistd.h>
#include "prototypes.h"
#include "structs.h"

void free_teams(myteams_t *teams)
{
    free_clients_list(teams->client_head);
    close(teams->server->control_socket);
    free(teams->server);
    free(teams);
}