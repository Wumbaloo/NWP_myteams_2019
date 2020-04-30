/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Where clients are free
*/

#include <stdlib.h>
#include "structs.h"

void free_client(client_t *client)
{
    if (client) {
        free(client->reply);
        free(client);
    }
}

void free_list(client_t *head)
{
    client_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free_client(head);
        head = tmp;
    }
    if (tmp)
        free_client(tmp);
}