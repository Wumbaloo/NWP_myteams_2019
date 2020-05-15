/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "clients_storage.h"

message_t *get_message(message_t *messages, uuid_t sender, uuid_t receiver,
    char body[DEFAULT_BODY_LENGTH + 1])
{
    message_t *copy = messages;

    for (; copy; copy = copy->next) {
        if (uuid_compare(copy->receiver, receiver) == 0 &&
        uuid_compare(copy->sender, sender) == 0
        && strcmp(body, copy->body) == 0)
            return copy;
    }
    return NULL;
}

message_t *new_message(uuid_t from, uuid_t to, char body[DEFAULT_BODY_LENGTH])
{
    message_t *msg = malloc(sizeof(message_t));

    if (!msg)
        perror_exit("malloc", 84);
    strcpy(msg->body, body);
    memcpy(msg->sender, from, 16);
    memcpy(msg->receiver, to, 16);
    msg->timestamp = time(NULL);
    msg->next = NULL;
    return msg;
}

void insert_message(message_t **first, uuid_t from, uuid_t to,
    char body[DEFAULT_BODY_LENGTH])
{
    message_t *copy = (*first);
    message_t *new_msg = new_message(from, to, body);

    if (!*first) {
        *first = new_msg;
        return;
    }
    for (; copy->next; copy = copy->next);
    copy->next = new_msg;
}