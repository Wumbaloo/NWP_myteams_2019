/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

void broadcast_unsubscription(client_t *client, char *team_uuid)
{
    char *reply;
    char user_uuid[36];

    uuid_unparse(client->user_uuid, user_uuid);
    reply = format_response(3, LEAVE_TEAM, user_uuid, team_uuid);
    insert_reply(&client->replies, reply);
    free(reply);
}

void broadcast_subscription(client_t *client, char *team_uuid)
{
    char *reply;
    char user_uuid[36];

    uuid_unparse(client->user_uuid, user_uuid);
    reply = format_response(3, JOIN_TEAM, user_uuid, team_uuid);
    insert_reply(&client->replies, reply);
    free(reply);
}