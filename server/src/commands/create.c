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
    subscribe_to_subchannels(&client->channel_tab, team);
    server_event_team_created(uuid, team->team_name, user_uuid);
    broadcast_team_created(teams, client, team);
    return (0);
}

void create_thread_sequel(myteams_t *teams, client_t *client,
    thread_t *thread, char **input)
{
    char thread_uuid[36];
    char user_uuid[36];
    comment_t *comment;

    comment = new_comment(input[1], client->user_uuid);
    if (!already_subscribed(client->thread_tab, thread->thread_uuid))
        insert_in_sub_list(&client->thread_tab, thread->thread_uuid);
    uuid_unparse(thread->thread_uuid, thread_uuid);
    uuid_unparse(client->user_uuid, user_uuid);
    server_event_thread_new_message(thread_uuid, user_uuid, input[1]);
    broadcast_comment_created(teams, client, comment);
}

int create_thread(myteams_t *teams, client_t *client, char **input)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;

    if (double_array_size(input) != 2)
        return (bad_cmd_parameters(client, input[0]));
    team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel = get_channel_by_uuid(team->channel_head, client->channel_chosen);
    thread = get_thread_by_uuid(channel->thread_head, client->thread_chosen);
    insert_comment(&thread->comment_head, input[1], client->user_uuid);
    create_thread_sequel(teams, client, thread, input);
    return (0);
}

int create_cmd(myteams_t *teams, client_t *client, char **input)
{
    if (!client->is_connected)
        return (reply_unauthorized(client));
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
    return (0);
}