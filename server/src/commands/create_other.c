/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Create team and channel
*/

#include <stdio.h>
#include <stdbool.h>
#include "logging_server.h"
#include "prototypes.h"
#include "structs.h"

void subscribe_all_clients(myteams_t *teams, team_t *team, channel_t *channel)
{
    client_t *copy = teams->client_head;

    for (; copy; copy = copy->next) {
        if (!already_subscribed(copy->team_tab, team->team_uuid))
            continue;
        insert_in_sub_list(&copy->channel_tab, channel->channel_uuid);
    }
}

int create_team(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    channel_t *channel;
    char chan_uuid[36];
    char team_uuid[36];

    if (double_array_size(input) != 3)
        return (bad_cmd_parameters(client, input[0]));
    team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel = get_channel_by_name(team->channel_head, input[1]);
    if (channel)
        return (reply_resource_already_exists(client));
    insert_channel(&team->channel_head, input[1], input[2]);
    channel = get_channel_by_name(team->channel_head, input[1]);
    subscribe_all_clients(teams, team, channel);
    uuid_unparse(channel->channel_uuid, chan_uuid);
    uuid_unparse(team->team_uuid, team_uuid);
    server_event_channel_created(team_uuid, chan_uuid, channel->channel_name);
    broadcast_channel_created(teams, client, channel);
    return (0);
}

int create_channel_next(thread_t **thread, channel_t *channel,
    client_t *client, char **input)
{
    (*thread) = get_thread_by_title(channel->thread_head, input[1]);
    if ((*thread))
        return (1);
    insert_thread(&channel->thread_head, input[1], input[2], client->user_uuid);
    (*thread) = new_thread(input[1], input[2], client->user_uuid);
    insert_in_sub_list(&client->thread_tab, (*thread)->thread_uuid);
    return (0);
}

int create_channel(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    char channel_uuid[36];
    char thread_uuid[36];
    char user_uuid[36];

    if (double_array_size(input) != 3)
        return (bad_cmd_parameters(client, input[0]));
    team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel = get_channel_by_uuid(team->channel_head, client->channel_chosen);
    if (!create_channel_next(&thread, channel, client, input))
        return (reply_resource_already_exists(client));
    uuid_unparse(channel->channel_uuid, channel_uuid);
    uuid_unparse(thread->thread_uuid, thread_uuid);
    uuid_unparse(client->user_uuid, user_uuid);
    server_event_thread_created(channel_uuid, thread_uuid,
        user_uuid, thread->thread_msg);
    broadcast_thread_created(teams, client, thread);
    return (0);
}