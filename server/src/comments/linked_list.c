/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include "data_storage.h"

comment_t *new_comment(char body[DEFAULT_BODY_LENGTH], uuid_t author)
{
    comment_t *comment = malloc(sizeof(comment_t));

    memcpy(comment->comment_author, author, 16);
    memcpy(comment->comment_body, body, DEFAULT_BODY_LENGTH);
    comment->timestamp = time(NULL);
    comment->next = NULL;
    return comment;
}

void insert_comment(comment_t **first, char body[DEFAULT_BODY_LENGTH],
    uuid_t author)
{
    comment_t *copy = *first;
    comment_t *comment = new_comment(body, author);

    if (!*first) {
        *first = comment;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = comment;
}