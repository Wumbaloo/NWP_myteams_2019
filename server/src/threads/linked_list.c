/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "data_storage.h"

thread_t *get_thread_by_title(thread_t *head, char *name)
{
    thread_t *copy = head;

    while (copy && strcmp(copy->thread_title, name))
        copy = copy->next;
    return (copy);
}

thread_t *get_thread_by_uuid(thread_t *head, uuid_t uuid)
{
    thread_t *copy = head;

    while (copy && uuid_compare(copy->thread_uuid, uuid))
        copy = copy->next;
    return (copy);
}

thread_t *new_thread(char *title, char *content, uuid_t author)
{
    thread_t *thread = malloc(sizeof(thread_t));

    if (!thread)
        perror_exit("malloc", 84);
    uuid_generate(thread->thread_uuid);
    uuid_copy(thread->thread_author, author);
    thread->timestamp = time(NULL);
    thread->thread_title = strdup(title);
    thread->thread_msg = strdup(content);
    thread->comment_head = NULL;
    thread->next = NULL;
    return (thread);
}

thread_t *insert_thread(thread_t **first, char *title, char *content, uuid_t author)
{
    thread_t *copy = *first;
    thread_t *thread = new_thread(title, content, author);

    if (!*first) {
        *first = thread;
        return (thread);
    }
    for (; copy->next; copy = copy->next);
    copy->next = thread;
    return (thread);
}