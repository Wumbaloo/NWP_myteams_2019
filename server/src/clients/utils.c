/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <stdlib.h>
#include "clients_storage.h"

void send_replies(client_t *first, fd_set wr_set)
{
    client_t *copy = first;

    while (copy) {
        if (FD_ISSET(copy->fd, &wr_set) && copy->reply) {
            dprintf(copy->fd, "%s\r\n", copy->reply);
            free(copy->reply);
            copy->reply = NULL;
        }
        copy = copy->next;
    }
}