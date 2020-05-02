/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"

void free_channel(channel_t *channel)
{
    if (channel->thread_head)
        free_threads_list(channel->thread_head);
}

void free_channels_list(channel_t *head)
{
    channel_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free_channel(head);
        free(head);
        head = tmp;
    }
}