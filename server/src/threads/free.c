/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"

void free_thread(thread_t *thread)
{
    if (thread->thread_title)
        free(thread->thread_title);
    if (thread->thread_msg)
        free(thread->thread_msg);
    if (thread->comment_head)
        free_comments_list(thread->comment_head);
}

void free_threads_list(thread_t *head)
{
    thread_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free_thread(head);
        free(head);
        head = tmp;
    }
}