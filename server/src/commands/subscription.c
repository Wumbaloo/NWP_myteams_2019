/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include "logging_server.h"
#include "prototypes.h"
#include "structs.h"

bool already_subscribed(sub_list_t *head, uuid_t team)
{
    sub_list_t *copy = head;

    for (; copy; copy = copy->next)
        if (!uuid_compare(copy->uuid, team))
            return true;
    return false;
}

void unsubscribe_from_sub_channels(sub_list_t *channel_list, team_t *team)
{
    channel_t *copy = team->channel_head;

    for (; copy; copy = copy->next)
        remove_in_sub_list(channel_list, copy->channel_uuid);
}

void unsubscribe_cmd(myteams_t *teams, client_t *client, char **input)
{
    client_t *client_tmp;
    team_t *to_unsubscribe;
    uuid_t temp;
    char uuid[36];

    if (client->is_connected == false) {
        //Error not logged
        return;
    }
    if (!input[1])
        //Error not enough arg
        return;
    uuid_parse(input[1], temp);
    to_unsubscribe = get_team_by_uuid(teams->team_head, temp);
    if (!to_unsubscribe) {
        //Error team not found
        return;
    } else if (already_subscribed(client->team_tab, temp) == false) {
        //Error not subscribed to the team
        return;
    }
    client_tmp = teams->client_head;
    for (; client_tmp; client_tmp = client_tmp->next) {
        if (uuid_compare(client->user_uuid, client_tmp->user_uuid) == 0) {
            remove_in_sub_list(client_tmp->team_tab, temp);
            unsubscribe_from_sub_channels(client_tmp->channel_tab, to_unsubscribe);
        }
    }
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_leave_a_team(input[1], uuid);
    //Announce the departure of the user ? Check Milanote
}

void subscribe_to_subchannels(sub_list_t *channel_list, team_t *team)
{
    channel_t *copy = team->channel_head;

    for (; copy; copy = copy->next)
        insert_in_sub_list(&channel_list, copy->channel_uuid);
}

void subscribe_cmd(myteams_t *teams, client_t *client, char **input)
{
    client_t *client_tmp;
    team_t *to_subscribe;
    uuid_t temp;
    char uuid[36];

    if (client->is_connected == false) {
        //Error not logged
        return;
    }
    if (!input[1])
        //Error not enough arg
        return;
    uuid_parse(input[1], temp);
    to_subscribe = get_team_by_uuid(teams->team_head, temp);
    if (!to_subscribe) {
        //Error unknown team
        return;
    } else if (already_subscribed(client->team_tab, temp)) {
        //Error already subscribed
        return;
    }
    client_tmp = teams->client_head;
    for (; client_tmp; client_tmp = client_tmp->next) {
        if (uuid_compare(client->user_uuid, client_tmp->user_uuid) == 0) {
            insert_in_sub_list(&client_tmp->team_tab, temp);
            subscribe_to_subchannels(client->channel_tab, to_subscribe);
        }
    }
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_join_a_team(input[1], uuid);
    //Announce the user entry in the group ? Check Milanote
}