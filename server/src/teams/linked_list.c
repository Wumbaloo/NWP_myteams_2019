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

team_t *get_team_by_name(team_t *head, char *name)
{
    team_t *copy = head;

    while (copy) {
        if (strcmp(copy->team_name, name) == 0)
            return copy;
        copy = copy->next;
    }
    return NULL;
}

team_t *get_team_by_uuid(team_t *head, uuid_t uuid)
{
    team_t *copy = head;

    while (copy) {
        if (uuid_compare(copy->team_uuid, uuid) == 0)
            return copy;
        copy = copy->next;
    }
    return NULL;
}

team_t *new_team(char name[DEFAULT_NAME_LENGTH + 1],
    char desc[DEFAULT_DESCRIPTION_LENGTH + 1])
{
    team_t *team = malloc(sizeof(team_t));

    if (!team)
        perror_exit("malloc", 84);
    uuid_generate(team->team_uuid);
    memset(team->team_name, '\0', DEFAULT_NAME_LENGTH + 1);
    for (int i = 0; name[i] && i < DEFAULT_NAME_LENGTH; i++)
        team->team_name[i] = name[i];
    memset(team->team_desc, '\0', DEFAULT_DESCRIPTION_LENGTH + 1);
    for (int i = 0; desc[i] && i < DEFAULT_DESCRIPTION_LENGTH; i++)
        team->team_desc[i] = desc[i];
    team->channel_head = NULL;
    team->next = NULL;
    return team;
}

void insert_team(team_t **first, char name[DEFAULT_NAME_LENGTH + 1],
    char desc[DEFAULT_DESCRIPTION_LENGTH + 1])
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