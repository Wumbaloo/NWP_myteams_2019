/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"
#include "structs.h"

void info_undefined(client_t *client)
{
    char uuid[36];
    char *reply;

    uuid_unparse(client->user_uuid, uuid);
    reply = format_response(4, INFO_USER, uuid, client->user_name, "1");
    insert_reply(&client->replies, reply);
    free(reply);
}

void info_team(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    char uuid[36];
    char *reply;

    uuid_unparse(team->team_uuid, uuid);
    reply = format_response(4, INFO_TEAM, uuid, team->team_name, team->team_desc);
    insert_reply(&client->replies, reply);
    free(reply);
}

void info_channel(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel_t *channel = get_channel_by_uuid(team->channel_head,
        client->channel_chosen);
    char uuid[36];
    char *reply;

    uuid_unparse(channel->channel_uuid, uuid);
    reply = format_response(4, INFO_CHANNEL, uuid, channel->channel_name,
        channel->channel_desc);
    insert_reply(&client->replies, reply);
    free(reply);
}

void info_thread(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel_t *channel = get_channel_by_uuid(team->channel_head,
        client->channel_chosen);
    thread_t *thread = get_thread_by_uuid(channel->thread_head,
        client->thread_chosen);
    char uuid[36];
    char user_uuid[36];
    char *reply;
    char timestamp[64];

    uuid_unparse(thread->thread_uuid, uuid);
    uuid_unparse(thread->thread_author, user_uuid);
    sprintf(timestamp, "%ld", thread->timestamp);
    reply = format_response(6, INFO_THREAD, uuid, user_uuid, timestamp,
        thread->thread_title, thread->thread_msg);
    insert_reply(&client->replies, reply);
    free(reply);
}

int info_cmd(myteams_t *teams, client_t *client, char **input)
{
    if (client->is_connected == false)
        return reply_unauthorized(client);
    if (double_array_size(input) != 1)
        //Error too much args
        return 1;
    switch (client->depth) {
        case UNDEFINED:
            info_undefined(client);
            break;
        case TEAM:
            info_team(teams, client);
            break;
        case CHANNEL:
            info_channel(teams, client);
            break;
        case THREAD:
            info_thread(teams, client);
            break;
    }
    return 0;
}