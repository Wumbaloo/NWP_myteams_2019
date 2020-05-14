/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Broadcast about login
*/

#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

void broadcast_login(client_t *head, char *uuid, char *user_name)
{
    client_t *copy = head;
    char *reply = format_response(3, CONNECTED, uuid, user_name);

    for (; copy; copy = copy->next) {
        if (copy->is_connected == true)
        insert_reply(&copy->replies, reply);
    }
    free(reply);
}

void broadcast_logout(client_t *head, char *uuid, char *user_name)
{
    client_t *copy = head;
    char *reply = format_response(3, DISCONNECTED, uuid, user_name);

    for (; copy; copy = copy->next)
        insert_reply(&copy->replies, reply);
    free(reply);
}