/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"

void free_team(team_t *team)
{
    if (team->channel_head)
        free_channels_list(team->channel_head);
}

void free_teams_list(team_t *head)
{
    team_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free_team(head);
        free(head);
        head = tmp;
    }
}