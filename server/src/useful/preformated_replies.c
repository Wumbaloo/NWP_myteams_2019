/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "clients_storage.h"
#include "prototypes.h"

int reply_unauthorized(client_t *client)
{
    char *reply = format_response(1, UNAUTHORIZED);

    insert_reply(&client->replies, reply);
    free(reply);
    return 0;
}

int reply_resource_already_exists(client_t *client)
{
    char *reply = format_response(1, ALREADY_EXISTS);

    insert_reply(&client->replies, reply);
    free(reply);
    return 0;
}