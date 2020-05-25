/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

int list_teams_subscribed(myteams_t *teams, client_t *client)
{
    sub_list_t *copy = client->team_tab;
    char *reply = NULL;
    team_t *subscribed = NULL;
    char uuid[36];

    for (; copy; copy = copy->next) {
        subscribed = get_team_by_uuid(teams->team_head, copy->uuid);
        uuid_unparse(subscribed->team_uuid, uuid);
        reply = format_response(4, LIST_TEAM, uuid, subscribed->team_name,
            subscribed->team_desc);
        insert_reply(&client->replies, reply);
        free(reply);
    }
    return (0);
}

void list_users_subscribed(client_t *head, uuid_t uuid, client_t *to_reply)
{
    client_t *copy = head;
    sub_list_t *banned = NULL;
    char *reply = NULL;
    char user_uuid[36];

    for (; copy; copy = copy->next) {
        if (already_subscribed(copy->team_tab, uuid) &&
            !is_banned(banned, copy->user_uuid)) {
            uuid_unparse(copy->user_uuid, user_uuid);
            reply = format_response(4, LIST_USERS, user_uuid, copy->user_name,
                copy->is_connected ? "1" : "0");
            insert_reply(&to_reply->replies, reply);
            free(reply);
            insert_in_sub_list(&banned, copy->user_uuid);
        }
    }
    free_sub_list(banned);
}

int subscribed_cmd(myteams_t *teams, client_t *client, char **arg)
{
    uuid_t temp;
    team_t *team_to_look;

    if (!client->is_connected)
        return (reply_unauthorized(client));
    if (!arg[1])
        return (list_teams_subscribed(teams, client));
    if (uuid_parse(arg[1], temp) == -1)
        return reply_unknown_team(client, arg[0]);
    team_to_look = get_team_by_uuid(teams->team_head, temp);
    if (!team_to_look)
        return (reply_unknown_team(client, arg[0]));
    else if (!already_subscribed(client->team_tab, temp))
        return (reply_unauthorized(client));
    list_users_subscribed(teams->client_head, temp, client);
    return (0);
}