/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Linked list for clients
*/

#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "structs.h"
#include "prototypes.h"

client_t *get_client(client_t *first, int fd)
{
    client_t *copy = first;

    while (copy && copy->fd != fd)
        copy = copy->next;
    return (copy);
}

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

client_t *new_node(int fd)
{
    client_t *elem = malloc(sizeof(client_t));

    if (!elem)
        perror_exit("malloc", 84);
    elem = new_client(fd);
    elem->next = NULL;
    return (elem);
}

void remove_client(client_t *first, int fd)
{
    client_t *copy = first;
    client_t *tmp = NULL;

    if (!first)
        return;
    for (; copy->next; copy = copy->next) {
        if (copy->next->fd == fd && copy->next->next) {
            tmp = copy->next;
            copy->next = copy->next->next;
            free_client(tmp);
            break;
        }
    }
}

void insert_client(client_t **first, int fd)
{
    client_t *copy = (*first);
    client_t *new = new_node(fd);

    if (!*first) {
        *first = new;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = new;
}