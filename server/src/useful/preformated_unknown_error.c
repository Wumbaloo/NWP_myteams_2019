/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"

int reply_unknown_user(client_t *client, char *user_uuid)
{
    char *reply = format_response(2, UNKNOWN_USER, user_uuid);

    insert_reply(&client->replies, reply);
    free(reply);
    return 0;
}

int reply_unknown_thread(client_t *client, char *thread_uuid)
{
    char *reply = format_response(2, UNKNOWN_THREAD, thread_uuid);

    insert_reply(&client->replies, reply);
    free(reply);
    return 0;
}

int reply_unknown_channel(client_t *client, char *channel_uuid)
{
    char *reply = format_response(2, UNKNOWN_CHANNEL, channel_uuid);

    insert_reply(&client->replies, reply);
    free(reply);
    return 0;
}

int reply_unknown_team(client_t *client, char *team_uuid)
{
    char *reply = format_response(2, UNKNOWN_TEAM, team_uuid);

    insert_reply(&client->replies, reply);
    free(reply);
    return 0;
}