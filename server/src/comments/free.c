/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "data_storage.h"

void free_comments_list(comment_t *head)
{
    comment_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}