/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include "clients_storage.h"

void remove_reply(replies_t *replies_head)
{
    replies_t *copy = replies_head;

    replies_head = copy->next;
    free(copy->reply);
    free(copy);
}

replies_t *new_reply(char *reply)
{
    replies_t *new = malloc(sizeof(replies_t));

    new->reply = strdup(reply);
    new->next = NULL;
    return new;
}

void insert_reply(replies_t **first, char *reply)
{
    replies_t *copy = *first;
    replies_t *to_add = new_reply(reply);

    if (!copy) {
        *first = to_add;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = to_add;
}