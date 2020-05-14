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

void list_undefined(myteams_t *teams, client_t *client)
{
    team_t *copy = teams->team_head;
    char uuid[36];
    char *reply;

    for (; copy; copy = copy->next) {
        uuid_unparse(copy->team_uuid, uuid);
        reply = format_response(4, LIST_TEAM, uuid, copy->team_name,
            copy->team_desc);
        insert_reply(&client->replies, reply);
        free(reply);
    }
}

void list_team(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel_t *copy = team->channel_head;
    char uuid[36];
    char *reply;

    for (; copy; copy = copy->next) {
        uuid_unparse(copy->channel_uuid, uuid);
        reply = format_response(4, LIST_CHANNEL, uuid, copy->channel_name,
            copy->channel_desc);
        insert_reply(&client->replies, reply);
        free(reply);
    }
}

void list_channel(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel_t *channel = get_channel_by_uuid(team->channel_head,
        client->channel_chosen);
    thread_t *copy = channel->thread_head;
    char thread_uuid[36];
    char author_uuid[36];
    char *reply;
    char timestamp[64];

    for (; copy; copy = copy->next) {
        uuid_unparse(copy->thread_uuid, thread_uuid);
        uuid_unparse(copy->thread_author, author_uuid);
        sprintf(timestamp, "%ld", copy->timestamp);
        reply = format_response(6, LIST_THREAD, thread_uuid, author_uuid,
            timestamp, copy->thread_title, copy->thread_msg);
        insert_reply(&client->replies, reply);
        free(reply);
    }
}

void list_thread(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel_t *channel = get_channel_by_uuid(team->channel_head,
        client->channel_chosen);
    thread_t *thread = get_thread_by_uuid(channel->thread_head,
        client->thread_chosen);
    comment_t *copy = thread->comment_head;
    char thread_uuid[36];
    char author_uuid[36];
    char timestamp[64];
    char *reply;

    for (; copy; copy = copy->next) {
        uuid_unparse(thread->thread_uuid, thread_uuid);
        uuid_unparse(thread->thread_author, author_uuid);
        sprintf(timestamp, "%ld", copy->timestamp);
        reply = format_response(5, LIST_REPLY, thread_uuid, author_uuid,
            timestamp, copy->comment_body);
        insert_reply(&client->replies, reply);
        free(reply);
    }
}

int list_cmd(myteams_t *teams, client_t *client, char **input)
{
    if (!client->is_connected)
        return (reply_unauthorized(client));
    else if (double_array_size(input) != 1)
        return (bad_cmd_parameters(client, input[0]));
    switch (client->depth) {
        case UNDEFINED:
            list_undefined(teams, client);
            break;
        case TEAM:
            list_team(teams, client);
            break;
        case CHANNEL:
            list_channel(teams, client);
            break;
        case THREAD:
            list_thread(teams, client);
            break;
    }
    return 0;
}