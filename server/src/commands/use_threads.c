/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Special file for the use command about threads
*/

#include <uuid/uuid.h>
#include <stdio.h>
#include "prototypes.h"

int end_use_thread(client_t *client, uuid_t team_uuid, thread_t *thread_head,
    char *thread_uuid_str)
{
    uuid_t thread_uuid;
    thread_t *thread;

    if (uuid_parse(thread_uuid_str, thread_uuid) == -1)
        return (reply_unknown_thread(client, thread_uuid_str));
    thread = get_thread_by_uuid(thread_head, thread_uuid);
    printf("Ok boomer\n");
    if (!thread)
        return (reply_unknown_thread(client, thread_uuid_str));
    uuid_copy(client->team_chosen, team_uuid);
    uuid_copy(client->thread_chosen, thread_uuid);
    client->depth = THREAD;
    printf("Successfully switched the thread\n");
    return (0);
}

int use_thread(myteams_t *teams, client_t *client, char **input)
{
    uuid_t team_uuid;
    uuid_t channel_uuid;
    team_t *team;
    channel_t *channel;

    if (uuid_parse(input[1], team_uuid) == -1)
        return (reply_unknown_team(client, input[1]));
    team = get_team_by_uuid(teams->team_head, team_uuid);
    if (!team)
        return (reply_unknown_team(client, input[1]));
    else if (uuid_parse(input[2], channel_uuid) == -1)
        return (reply_unknown_channel(client, input[2]));
    channel = get_channel_by_uuid(team->channel_head, channel_uuid);
    if (!channel)
        return (reply_unknown_channel(client, input[2]));
    uuid_copy(client->channel_chosen, channel_uuid);
    return (end_use_thread(client, team_uuid, channel->thread_head, input[3]));
}