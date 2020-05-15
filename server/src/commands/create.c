/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <stdbool.h>
#include "logging_server.h"
#include "prototypes.h"
#include "structs.h"

int create_undefined(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    char uuid[36];
    char user_uuid[36];

    if (double_array_size(input) != 3)
        return (bad_cmd_parameters(client, input[0]));
    team = get_team_by_name(teams->team_head, input[1]);
    if (team)
        return (reply_resource_already_exists(client));
    insert_team(&teams->team_head, input[1], input[2]);
    team = get_team_by_name(teams->team_head, input[1]);
    uuid_unparse(team->team_uuid, uuid);
    uuid_unparse(client->user_uuid, user_uuid);
    insert_in_sub_list(&client->team_tab, team->team_uuid);
    subscribe_to_subchannels(client->channel_tab, team);
    server_event_team_created(uuid, team->team_name, user_uuid);
    broadcast_team_created(teams, client, team);
    return (0);
}

int create_team(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    channel_t *channel;
    client_t *copy;
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
    //Subscribe all the clients to the channel
    copy = teams->client_head;
    for (; copy; copy = copy->next) {
        if (!already_subscribed(copy->team_tab, team->team_uuid))
            continue;
        insert_in_sub_list(&copy->channel_tab, channel->channel_uuid);
    }
    uuid_unparse(channel->channel_uuid, chan_uuid);
    uuid_unparse(team->team_uuid, team_uuid);
    server_event_channel_created(team_uuid, chan_uuid, channel->channel_name);
    broadcast_channel_created(teams, client, channel);
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
    thread = get_thread_by_title(channel->thread_head, input[1]);
    if (thread)
        return (reply_resource_already_exists(client));
    insert_thread(&channel->thread_head, input[1], input[2], client->user_uuid);
    thread = new_thread(input[1], input[2], client->user_uuid);
    insert_in_sub_list(&client->thread_tab, thread->thread_uuid);
    uuid_unparse(channel->channel_uuid, channel_uuid);
    uuid_unparse(thread->thread_uuid, thread_uuid);
    uuid_unparse(client->user_uuid, user_uuid);
    server_event_thread_created(channel_uuid, thread_uuid,
        user_uuid, thread->thread_msg);
    broadcast_thread_created(teams, client, thread);
    return (0);
}

void create_thread(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    comment_t *comment;
    char thread_uuid[36];
    char user_uuid[36];

    if (double_array_size(input) != 2) {
        printf("Array size = %d\n", double_array_size(input));
        bad_cmd_parameters(client, input[0]);
        return;
    }
    team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel = get_channel_by_uuid(team->channel_head, client->channel_chosen);
    thread = get_thread_by_uuid(channel->thread_head, client->thread_chosen);
    insert_comment(&thread->comment_head, input[1], client->user_uuid);
    comment = new_comment(input[1], client->user_uuid);
    if (!already_subscribed(client->thread_tab, thread->thread_uuid))
        insert_in_sub_list(&client->thread_tab, thread->thread_uuid);
    uuid_unparse(thread->thread_uuid, thread_uuid);
    uuid_unparse(client->user_uuid, user_uuid);
    broadcast_comment_created(teams, client, comment);
    server_event_thread_new_message(thread_uuid, user_uuid, input[1]);
}

int create_cmd(myteams_t *teams, client_t *client, char **input)
{
    if (!client->is_connected)
        return (reply_unauthorized(client));
    switch (client->depth) {
        case UNDEFINED:
            create_undefined(teams, client, input);
            break;
        case TEAM:
            create_team(teams, client, input);
            break;
        case CHANNEL:
            printf("Creating a thread\n");
            create_channel(teams, client, input);
            break;
        case THREAD:
            printf("Creating a reply\n");
            create_thread(teams, client, input);
            break;
    }
    return (0);
}