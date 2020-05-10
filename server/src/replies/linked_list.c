/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "clients_storage.h"

void remove_reply(replies_t **replies_head)
{
    replies_t *tmp;

    if (!*replies_head)
        return;
    tmp = (*replies_head)->next;
    if ((*replies_head)->reply)
        free((*replies_head)->reply);
    free(*replies_head);
    *replies_head = tmp;
}

replies_t *new_reply(char *reply)
{
    replies_t *new = malloc(sizeof(replies_t));

    if (!new)
        perror_exit("malloc", 84);
    new->reply = strdup(reply);
    if (!new->reply)
        perror_exit("malloc", 84);
    new->next = NULL;
    return (new);
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