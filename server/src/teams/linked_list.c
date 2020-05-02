/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "data_storage.h"

team_t *new_team(char name[DEFAULT_NAME_LENGTH],
    char desc[DEFAULT_DESCRIPTION_LENGTH])
{
    team_t *team = malloc(sizeof(team_t));

    if (!team)
        perror_exit("malloc", 84);
    uuid_generate(team->team_uuid);
    memcpy(team->team_name, name, DEFAULT_NAME_LENGTH);
    memcpy(team->team_desc, desc, DEFAULT_DESCRIPTION_LENGTH);
    team->channel_head = NULL;
    team->next = NULL;
    return team;
}

void insert_team(team_t **first, char name[DEFAULT_NAME_LENGTH],
    char desc[DEFAULT_DESCRIPTION_LENGTH])
{
    team_t *copy = *first;
    team_t *team = new_team(name, desc);

    if (!*first) {
        *first = team;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = team;
}