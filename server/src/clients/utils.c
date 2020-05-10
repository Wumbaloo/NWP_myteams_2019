/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "prototypes.h"
#include "clients_storage.h"

void copy_subscribed(client_t *src, client_t *dest)
{
    sub_list_t *copy = src->team_tab;

    for (; copy; copy = copy->next)
        insert_in_sub_list(&dest->team_tab, copy->uuid);
    copy = src->channel_tab;
    for (; copy; copy = copy->next)
        insert_in_sub_list(&dest->channel_tab, copy->uuid);
    copy = src->thread_tab;
    for (; copy; copy = copy->next)
        insert_in_sub_list(&dest->thread_tab, copy->uuid);
}

int nbr_duplicates(client_t *head, uuid_t uuid)
{
    client_t *copy = head;
    int cpt = 0;

    for (; copy; copy = copy->next)
        if (uuid_compare(copy->user_uuid, uuid) == 0)
            cpt++;
    return cpt;
}

void duplicate_client(client_t *src, client_t *dest)
{
    message_t *copy = src->message_head;
    message_t *temp;

    dest->is_connected = true;
    memcpy(dest->user_name, src->user_name, DEFAULT_NAME_LENGTH);
    uuid_copy(dest->user_uuid, src->user_uuid);
    dest->depth = src->depth;
    uuid_copy(dest->team_chosen, src->team_chosen);
    uuid_copy(dest->channel_chosen, src->channel_chosen);
    uuid_copy(dest->thread_chosen, src->thread_chosen);
    copy_subscribed(src, dest);
    dest->message_head = NULL;
    for (; copy; copy = copy->next)
        insert_message(&dest->message_head, copy->sender, copy->receiver,
            copy->body);
    copy = dest->message_head;
    temp = src->message_head;
    for (; copy && temp; copy = copy->next, temp = temp->next)
        copy->timestamp = temp->timestamp;
}

void send_next_reply(myteams_t *team, int fd)
{
    client_t *client = get_client_by_fd(team->client_head, fd);

    if (client->replies) {
        dprintf(fd, "%s\r\n", client->replies->reply);
        remove_reply(&client->replies);
    }
}