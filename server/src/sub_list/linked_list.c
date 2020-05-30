/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"
#include "clients_storage.h"

sub_list_t *new_in_sublist(uuid_t uuid)
{
    sub_list_t *new = malloc(sizeof(sub_list_t));

    if (!new)
        perror_exit("malloc", 84);
    uuid_copy(new->uuid, uuid);
    new->next = NULL;
    return new;
}

#include <stdio.h>
int remove_in_sub_list(sub_list_t *first, uuid_t uuid)
{
    sub_list_t *copy = first;
    sub_list_t *tmp = NULL;

    if (!first)
        return (0);
    if (copy != NULL && !uuid_compare(uuid, copy->uuid)) {
        first = copy->next;
        free(copy);
        return (0);
    }
    while (copy != NULL && uuid_compare(uuid, copy->uuid)) {
        tmp = copy;
        copy = copy->next;
    }
    if (!copy)
        return (0);
    tmp->next = copy->next;
    if (first == tmp)
        return (1);
    free(copy);
    return (0);
}

void insert_in_sub_list(sub_list_t **first, uuid_t uuid)
{
    sub_list_t *copy = *first;
    sub_list_t *to_add = new_in_sublist(uuid);

    if (!*first) {
        *first = to_add;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = to_add;
}