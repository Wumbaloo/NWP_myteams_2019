/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Where clients are free
*/

#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

void free_sub_list(sub_list_t *list)
{
    sub_list_t *copy = NULL;

    for (; list; list = copy) {
        copy = list->next;
        free(list);
    }
}

void free_replies(replies_t *head)
{
    replies_t *tmp = NULL;

    for (; head; head = tmp) {
        tmp = head->next;
        free(head->reply);
        free(head);
    }
}

void free_client(client_t *client)
{
    free_sub_list(client->team_tab);
    free_sub_list(client->channel_tab);
    free_sub_list(client->thread_tab);
    if (client->message_head)
        free_messages_list(client->message_head);
    if (client->replies)
        free_replies(client->replies);
}

void free_clients_list(client_t *head)
{
    client_t *tmp = NULL;

    while (head) {
        if (head->fd != -1)
            close(head->fd);
        tmp = head->next;
        free_client(head);
        free(head);
        head = tmp;
    }
}