/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <stdio.h>
#include "ftp.h"
#include "prototypes.h"

client_t *get_client(element *first, int fd)
{
    element *copy = first;

    while (copy->client->fd != fd)
        copy = copy->next;
    return copy->client;
}

void send_replies(element *first, fd_set wr_set)
{
    element *copy = first;

    copy = copy->next;
    while (copy) {
        if (FD_ISSET(copy->client->fd, &wr_set) && copy->client->reply) {
            dprintf(copy->client->fd, "%s\r\n", copy->client->reply);
            free(copy->client->reply);
            copy->client->reply = NULL;
        }
        copy = copy->next;
    }
}

element *new_node(int fd, char *path)
{
    element *elem = malloc(sizeof(element));

    elem->client = new_client(fd, path);
    elem->next = NULL;
    return elem;
}

void remove_client(element *first, int fd)
{
    element *copy = first;
    element *temp = NULL;

    while (copy->client->fd != fd) {
        temp = copy;
        copy = copy->next;
    }
    temp->next = copy->next;
    free_client(copy->client);
    free(copy);
}

void insert_client(element *first, int fd, char *path)
{
    element *copy = first;

    while (copy->next != NULL)
        copy = copy->next;
    copy->next = new_node(fd, path);
}