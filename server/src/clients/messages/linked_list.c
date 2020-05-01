/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include "clients_storage.h"

message_t *new_message(uuid_t from, uuid_t to, char body[DEFAULT_BODY_LENGTH])
{
    message_t *msg = malloc(sizeof(message_t));

    strcpy(msg->body, body);
    memcpy(msg->sender, from, 16);
    memcpy(msg->receiver, to, 16);
    msg->next = NULL;
    return msg;
}

void insert_message(message_t **first, uuid_t from, uuid_t to, char body[DEFAULT_BODY_LENGTH])
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