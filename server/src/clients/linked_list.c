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

int nbr_clients(client_t *head)
{
    int nbr = 0;
    client_t *copy = head;

    for (; copy; copy = copy->next)
        nbr++;
    return nbr;
}

client_t *new_client(int fd)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client)
        perror_exit("malloc", 84);
    memset(client->user_name, '\0', DEFAULT_NAME_LENGTH);
    client->depth = UNDEFINED;
    client->team_tab = NULL;
    client->channel_tab = NULL;
    client->thread_tab = NULL;
    client->fd = fd;
    client->is_connected = false;
    client->reply = NULL;
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
    //A changer: voir sub_list/linked_list.c
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
    client_t *new = new_client(fd);

    if (!*first) {
        *first = new;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = new;
}