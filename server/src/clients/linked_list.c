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

    while (copy->fd != fd)
        copy = copy->next;
    return (copy);
}

void send_replies(client_t *first, fd_set wr_set)
{
    client_t *copy = first;

    copy = copy->next;
    while (copy) {
        if (FD_ISSET(copy->fd, &wr_set) && copy->reply) {
            dprintf(copy->fd, "%s\r\n", copy->reply);
            free(copy->reply);
            copy->reply = NULL;
        }
        copy = copy->next;
    }
}

client_t *new_node(int fd, char *path)
{
    client_t *elem = malloc(sizeof(client_t));

    if (!elem) {
        perror("malloc");
        exit(84);
    }
    elem = new_client(fd, path);
    elem->next = NULL;
    return (elem);
}

void remove_client(client_t *first, int fd)
{
    client_t *copy = first;
    client_t *temp = NULL;

    while (copy->fd != fd) {
        temp = copy;
        copy = copy->next;
    }
    temp->next = copy->next;
    free_client(copy);
    free(copy);
}

void insert_client(client_t *first, int fd, char *path)
{
    client_t *copy = first;

    while (copy->next != NULL)
        copy = copy->next;
    copy->next = new_node(fd, path);
}