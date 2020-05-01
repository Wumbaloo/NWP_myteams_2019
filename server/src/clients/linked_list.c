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
    memset(client->user_name, '\0', DEFAULT_NAME_LENGTH);
    uuid_generate_random(client->user_uuid);
    client->depth = TEAM;
    client->group_tab = NULL;
    client->channel_tab = NULL;
    client->thread_tab = NULL;
    client->comment_tab = NULL;
    client->fd = fd;
    client->is_connected = false;
    client->reply = NULL;
    client->message_head = NULL;
    return (client);
}

client_t *get_client(client_t *first, int fd)
{
    client_t *copy = first;

    while (copy && copy->fd != fd)
        copy = copy->next;
    return (copy);
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