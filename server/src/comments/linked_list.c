/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "data_storage.h"

comment_t *new_comment(char body[DEFAULT_BODY_LENGTH], uuid_t author)
{
    comment_t *comment = malloc(sizeof(comment_t));

    if (!comment)
        perror_exit("malloc", 84);
    uuid_copy(comment->comment_author, author);
    memset(comment->comment_body, '\0', DEFAULT_BODY_LENGTH + 1);
    for (int i = 0; body[i] && i < DEFAULT_BODY_LENGTH; i++)
        comment->comment_body[i] = body[i];
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