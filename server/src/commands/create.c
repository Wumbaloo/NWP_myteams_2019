/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include "prototypes.h"
#include "structs.h"

void create_undefined(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    client_t *copy;

    if (double_array_size(input) != 3) {
        bad_cmd_parameters(client, input[0]);
        return;
    }
    team = get_team_by_name(teams->team_head, input[1]);
    if (team)
        //Error : Team already exists
        return;
    insert_team(&teams->team_head, input[1], input[2]);
    team = get_team_by_name(teams->team_head, input[1]);
    copy = teams->client_head;
    for (; copy; copy = copy->next) {
        if (uuid_compare(copy->user_uuid, client->user_uuid))
            continue;
        insert_in_sub_list(&copy->team_tab, team->team_uuid);
        subscribe_to_subchannels(copy->channel_tab, team);
    }
}

void create_team(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    channel_t *channel;
    client_t *copy;
    char uuid[36];

    if (double_array_size(input) != 3) {
        bad_cmd_parameters(client, input[0]);
        return;
    }
    team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel = get_channel_by_name(team->channel_head, input[1]);
    if (channel)
        //Error: already exists
        return;
    insert_channel(&team->channel_head, input[1], input[2]);
    channel = get_channel_by_name(team->channel_head, input[1]);
    //Subscribe all the clients to the channel
    copy = teams->client_head;
    for (; copy; copy = copy->next) {
        if (!already_subscribed(copy->team_tab, team->team_uuid))
            continue;
        insert_in_sub_list(&copy->channel_tab, channel->channel_uuid);
    }
    uuid_unparse(channel->channel_uuid, uuid);
    //Send to user: channel_uuid + channel_name + channel_desc
}

void create_channel(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    char uuid[36];

    if (double_array_size(input) != 3) {
        bad_cmd_parameters(client, input[0]);
        return;
    }
    team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel = get_channel_by_uuid(team->channel_head, client->channel_chosen);
    thread = get_thread_by_title(channel->thread_head, input[1]);
    if (thread)
        //Error already exists
        return;
    insert_thread(&channel->thread_head, input[1], input[2], client->user_uuid);
    thread = new_thread(input[1], input[2], client->user_uuid);
    uuid_unparse(thread->thread_uuid, uuid);
    //Send to user: thread_uuid + author_uuid + timestamp + thread_title + thread_body
}

void create_thread(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    comment_t *comment;
    char team_uuid[36];
    char thread_uuid[36];
    char user_uuid[36];

    if (double_array_size(input) != 2) {
        bad_cmd_parameters(client, input[0]);
        return;
    }
    team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel = get_channel_by_uuid(team->channel_head, client->channel_chosen);
    thread = get_thread_by_uuid(channel->thread_head, client->thread_chosen);
    insert_comment(&thread->comment_head, input[1], client->user_uuid);
    comment = new_comment(input[1], client->user_uuid);
    uuid_unparse(team->team_uuid, team_uuid);
    uuid_unparse(thread->thread_uuid, thread_uuid);
    uuid_unparse(client->user_uuid, user_uuid);
    (void)(comment);
    //Send to user : team_uuid + thread_uuid + user_uuid + message_body
}

void create_cmd(myteams_t *teams, client_t *client, char **input)
{
    if (!client->is_connected) {
        not_logged_in(client);
        return;
    }
    switch (client->depth) {
        case TEAM:
            create_team(teams, client, input);
            break;
        case CHANNEL:
            create_channel(teams, client, input);
            break;
        case THREAD:
            create_thread(teams, client, input);
            break;
        default:
        case UNDEFINED:
            create_undefined(teams, client, input);
            break;
    }
}