/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

void broadcast_team_created(myteams_t *teams, client_t *client, team_t *team)
{
    client_t *copy = teams->client_head;
    char uuid[36];
    char *reply_user;
    char *reply_specific;

    uuid_unparse(team->team_uuid, uuid);
    reply_user = format_response(4, TEAM_CREATED, uuid,
        team->team_name, team->team_desc);
    reply_specific = format_response(4, SUCCESS_CREATED_TEAM, uuid,
        team->team_name, team->team_desc);
    for (; copy; copy = copy->next) {
        if (copy == client)
            insert_reply(&copy->replies, reply_specific);
        else
            insert_reply(&copy->replies, reply_user);
    }
    free(reply_specific);
    free(reply_user);
}

void broadcast_channel_created(myteams_t *teams, client_t *client,
    channel_t *channel)
{
    client_t *copy = teams->client_head;
    char uuid[36];
    char *reply_user;
    char *reply_specific;

    uuid_unparse(channel->channel_uuid, uuid);
    reply_user = format_response(4, CHANNEL_CREATED, uuid,
        channel->channel_name, channel->channel_desc);
    reply_specific = format_response(4, SUCCESS_CREATED_CHANNEL, uuid,
        channel->channel_name, channel->channel_desc);
    for (; copy; copy = copy->next) {
        if (copy == client)
            insert_reply(&copy->replies, reply_specific);
        else
            insert_reply(&copy->replies, reply_user);
    }
    free(reply_specific);
    free(reply_user);
}

void broadcast_thread_created(myteams_t *teams, client_t *client,
    thread_t *thread)
{
    client_t *copy = teams->client_head;
    char *reply_user;
    char *reply_specific;
    char thread_uuid[36];
    char user_uuid[36];
    char timestamp[64];

    uuid_unparse(client->user_uuid, user_uuid);
    uuid_unparse(thread->thread_uuid, thread_uuid);
    sprintf(timestamp, "%ld", thread->timestamp);
    reply_specific = format_response(5, SUCCESS_CREATED_THREAD, thread_uuid,
        user_uuid, timestamp, thread->thread_title, thread->thread_msg);
    reply_user = format_response(5, THREAD_CREATED, thread_uuid,
        user_uuid, timestamp, thread->thread_title, thread->thread_msg);
    for (; copy; copy = copy->next)
        if (copy == client)
            insert_reply(&copy->replies, reply_specific);
        else if (already_subscribed(copy->channel_tab, client->channel_chosen))
            insert_reply(&copy->replies, reply_user);
    free(reply_specific);
    free(reply_user);
}

void broadcast_comment_created(myteams_t *teams, client_t *client,
    comment_t *comment)
{
    client_t *copy = teams->client_head;
    char *reply_user;
    char *reply_specific;
    char team_uuid[36];
    char thread_uuid[36];
    char user_uuid[36];
    char timestamp[64];

    sprintf(timestamp, "%ld", comment->timestamp);
    uuid_unparse(client->team_chosen, team_uuid);
    uuid_unparse(client->thread_chosen, thread_uuid);
    uuid_unparse(client->user_uuid, user_uuid);
    reply_specific = format_response(5, SUCCESS_REPLY_POSTED, thread_uuid,
        user_uuid, timestamp, comment->comment_body);
    reply_user = format_response(5, REPLY_POSTED, team_uuid, thread_uuid,
        user_uuid, comment->comment_body);
    for (; copy; copy = copy->next)
        if (copy == client)
            insert_reply(&copy->replies, reply_specific);
        else if (already_subscribed(copy->thread_tab, client->thread_chosen))
            insert_reply(&copy->replies, reply_user);
    free(reply_user);
    free(reply_specific);
}