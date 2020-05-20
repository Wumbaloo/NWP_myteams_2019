/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Linked list for clients
*/

#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>
#include "structs.h"
#include "prototypes.h"

client_t *new_client(int fd)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client)
        perror_exit("malloc", 84);
    memset(client->user_name, '\0', DEFAULT_NAME_LENGTH + 1);
    client->depth = UNDEFINED;
    uuid_clear(client->user_uuid);
    uuid_clear(client->team_chosen);
    uuid_clear(client->channel_chosen);
    uuid_clear(client->thread_chosen);
    client->team_tab = NULL;
    client->channel_tab = NULL;
    client->thread_tab = NULL;
    client->fd = fd;
    client->is_connected = false;
    client->replies = NULL;
    client->message_head = NULL;
    client->next = NULL;
    return (client);
}

void remove_client(client_t *first, int fd)
{
    client_t *copy = first;
    client_t *tmp = NULL;

    if (!first)
        return;
    if (copy != NULL && copy->fd == fd) {
        first = copy->next;
        free_client(copy);
        free(copy);
        return;
    }
    while (copy != NULL && copy->fd != fd) {
        tmp = copy;
        copy = copy->next;
    }
    if (!copy)
        return;
    tmp->next = copy->next;
    free_client(copy);
    free(copy);
}

void insert_client(client_t **first, int fd)
{
    client_t *copy = (*first);
    client_t *new = new_client(fd);

    if (!*first) {
        *first = new;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = new;
}