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

thread_t *new_thread(char *title, char *content, uuid_t author)
{
    thread_t *thread = malloc(sizeof(thread_t));

    if (!thread)
        perror_exit("malloc", 84);
    uuid_generate(thread->thread_uuid);
    memcpy(thread->thread_author, author, 16);
    thread->thread_title = strdup(title);
    thread->thread_msg = strdup(content);
    thread->comment_head = NULL;
    thread->next = NULL;
    return thread;
}

void insert_thread(thread_t **first, char *title, char *content, uuid_t author)
{
    thread_t *copy = *first;
    thread_t *thread = new_thread(title, content, author);

    if (!*first) {
        *first = thread;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = thread;
}