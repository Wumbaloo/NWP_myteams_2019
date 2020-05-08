/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include "prototypes.h"
#include "structs.h"

void list_undefined(myteams_t *teams, client_t *client)
{
    team_t *copy = teams->team_head;
    char uuid[36];

    (void)(client);
    for (; copy; copy = copy->next) {
        uuid_unparse(copy->team_uuid, uuid);
        //Send to the user : uuid + team_name + team_desc
    }
}

void list_team(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel_t *copy = team->channel_head;
    char uuid[36];

    for (; copy; copy = copy->next) {
        uuid_unparse(copy->channel_uuid, uuid);
        //Send to user: uuid + channel_name + channel_desc
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

    for (; copy; copy = copy->next) {
        uuid_unparse(copy->thread_uuid, thread_uuid);
        uuid_unparse(copy->thread_author, author_uuid);
        //Send to user: thread_uuid + user_uuid + thread_timestamp + thread_title + thread_body
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

    for (; copy; copy = copy->next) {
        uuid_unparse(thread->thread_uuid, thread_uuid);
        uuid_unparse(thread->thread_author, author_uuid);
        //Send to user: thread_uuid + user_uuid + reply_timestamp + reply_body
    }
}

void list_cmd(myteams_t *teams, client_t *client, char **input)
{
    if (client->is_connected == false) {
        not_logged_in(client);
        return;
    }
    if (double_array_size(input) != 1) {
        //Error too much args
        return;
    }
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
        default:
            break;
    }
}