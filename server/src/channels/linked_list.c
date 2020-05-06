/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include "data_storage.h"
#include "prototypes.h"

channel_t *get_channel_by_name(channel_t *head, char *name)
{
    channel_t *copy = head;

    while (copy && strcmp(copy->channel_name, name))
        copy = copy->next;
    return copy;
}

channel_t *get_channel_by_uuid(channel_t *head, uuid_t uuid)
{
    channel_t *copy = head;

    while (copy && uuid_compare(copy->channel_uuid, uuid))
        copy = copy->next;
    return copy;
}

channel_t *new_channel(char name[DEFAULT_NAME_LENGTH],
    char desc[DEFAULT_DESCRIPTION_LENGTH])
{
    channel_t *channel = malloc(sizeof(channel_t));

    if (!channel)
        perror_exit("malloc", 84);
    uuid_generate(channel->channel_uuid);
    memcpy(channel->channel_name, name, DEFAULT_NAME_LENGTH);
    memcpy(channel->channel_desc, desc, DEFAULT_DESCRIPTION_LENGTH);
    channel->thread_head = NULL;
    channel->next = NULL;
    return channel;
}

void insert_channel(channel_t **first, char name[DEFAULT_NAME_LENGTH],
    char desc[DEFAULT_DESCRIPTION_LENGTH])
{
    channel_t *copy = *first;
    channel_t *channel = new_channel(name, desc);

    if (!*first) {
        *first = channel;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = channel;
}