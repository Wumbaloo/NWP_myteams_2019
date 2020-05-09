/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Where clients are free
*/

#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

void free_client(client_t *client)
{
//    if (client->group_tab)
//        free(client->group_tab);
    if (client->channel_tab)
        free(client->channel_tab);
    if (client->thread_tab)
        free(client->thread_tab);
    if (client->message_head)
        free_messages_list(client->message_head);
}

void free_clients_list(client_t *head)
{
    client_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free_client(head);
        free(head);
        head = tmp;
    }
}