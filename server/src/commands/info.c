/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include "prototypes.h"
#include "structs.h"

void info_undefined(myteams_t *teams, client_t *client)
{
    client_t *copy;
    sub_list_t *banned = NULL;

    copy = teams->client_head;
    for (; copy; copy = copy->next) {
        if (is_banned(banned, copy->user_uuid) || !copy->is_connected)
            continue;
        //Send to the user : uuid + user_name + user_status
        insert_in_sub_list(&banned, copy->user_uuid);
    }
}

void info_team(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    char uuid[36];

    uuid_unparse(team->team_uuid, uuid);
    //Send to user: uuid + team_name + team_desc
}

void info_channel(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel_t *channel = get_channel_by_uuid(team->channel_head,
        client->channel_chosen);
    char uuid[36];

    uuid_unparse(channel->channel_uuid, uuid);
    //Send to user: uuid + channel_name + channel desc
}

void info_thread(myteams_t *teams, client_t *client)
{
    team_t *team = get_team_by_uuid(teams->team_head, client->team_chosen);
    channel_t *channel = get_channel_by_uuid(team->channel_head,
        client->channel_chosen);
    thread_t *thread = get_thread_by_uuid(channel->thread_head, client->thread_chosen);
    char uuid[36];

    uuid_unparse(thread->thread_uuid, uuid);
    //Send to user: uuid + user_uuid + thread_timestamp + thread_title + thread_body
}

void info_cmd(myteams_t *teams, client_t *client, char **input)
{
    if (client->is_connected == false)
        //Error not logged
        return;
    if (double_array_size(input) != 1)
        //Error too much args
        return;
    switch (client->depth) {
        case UNDEFINED:
            info_undefined(teams, client);
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
}