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

void copy_array(uuid_t *src, uuid_t *dest)
{
    int size = uuid_tab_size(src);

    dest = malloc(sizeof(uuid_t) * (size + 1));
    memcpy(dest, src, size);
}

void duplicate_client(client_t *src, client_t *dest)
{
    message_t *copy = src->message_head;
    dest->is_connected = true;
    memcpy(dest->user_name, src->user_name, DEFAULT_NAME_LENGTH);
    uuid_copy(dest->user_uuid, src->user_uuid);
    dest->depth = src->depth;
    copy_array(src->group_tab, dest->group_tab);
    copy_array(src->channel_tab, dest->channel_tab);
    copy_array(src->thread_tab, dest->thread_tab);
    dest->message_head = NULL;
    for (; copy; copy = copy->next)
        insert_message(&dest->message_head, copy->sender, copy->receiver,
            copy->body);
    console_log(dest, " has been duplicated", SUCCESS, NULL);
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