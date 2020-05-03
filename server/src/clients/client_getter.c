/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <string.h>
#include "clients_storage.h"

client_t *get_client_by_fd(client_t *head, int fd)
{
    client_t *copy = head;

    while (copy && copy->fd != fd)
        copy = copy->next;
    return (copy);
}

client_t *get_client_by_uuid(client_t *head, uuid_t uuid)
{
    client_t *copy = head;

    while (copy && uuid_compare(uuid, copy->user_uuid))
        copy = copy->next;
    return copy;
}

client_t *get_client_by_username(client_t *head, char *username)
{
    client_t *copy = head;

    while (copy && strcmp(username, copy->user_name))
        copy = copy->next;
    return copy;
}