/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "clients_storage.h"

void free_messages_list(message_t *head)
{
    message_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}