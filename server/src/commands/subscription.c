/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include "logging_server.h"
#include "structs.h"
#include "prototypes.h"

bool already_subscribed(sub_list_t *head, uuid_t team)
{
    sub_list_t *copy = head;

    if (!head)
        return (false);
    for (; copy; copy = copy->next)
        if (!uuid_compare(copy->uuid, team))
            return (true);
    return (false);
}

void unsubscribe_from_sub_channels(sub_list_t *channel_list, team_t *team)
{
    channel_t *copy = team->channel_head;

    for (; copy; copy = copy->next)
        remove_in_sub_list(channel_list, copy->channel_uuid);
}

void subscribe_to_subchannels(sub_list_t **channel_list, team_t *team)
{
    channel_t *copy = team->channel_head;

    for (; copy; copy = copy->next) {
        insert_in_sub_list(channel_list, copy->channel_uuid);
        printf("Inserted a channel to the list\n");
    }
}