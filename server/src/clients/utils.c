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

void duplicate_client(client_t *src, client_t *dest)
{
    message_t *copy = src->message_head;
    message_t *temp;

    dest->is_connected = true;
    memcpy(dest->user_name, src->user_name, DEFAULT_NAME_LENGTH);
    uuid_copy(dest->user_uuid, src->user_uuid);
    dest->depth = src->depth;
    copy_subscribed(src, dest);
    dest->message_head = NULL;
    for (; copy; copy = copy->next)
        insert_message(&dest->message_head, copy->sender, copy->receiver,
            copy->body);
    copy = dest->message_head;
    temp = src->message_head;
    for (; copy && temp; copy = copy->next, temp = temp->next)
        copy->timestamp = temp->timestamp;
    //copie des commandes ?
}

void send_replies(myteams_t *teams, client_t *first, fd_set wr_set)
{
    client_t *copy = first;

    while (copy) {
        if (FD_ISSET(copy->fd, &wr_set) && copy->reply) {
            dprintf(copy->fd, "%s\r\n", copy->reply);
            if (strstr(copy->reply, "231")) {
                close(copy->fd);
                teams->clients[teams->act_idx] = 0;
            }
            free(copy->reply);
            copy->reply = NULL;
        }
        copy = copy->next;
    }
}