/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include "prototypes.h"
#include "structs.h"

void list_teams_subscribed(sub_list_t *team_list)
{
    sub_list_t *copy = team_list;

    for (; copy; copy = copy->next) {
        //Send user: team_uuid + tema_name + team_desc
    }
}

void list_users_subscribed(client_t *head, uuid_t uuid)
{
    client_t *copy = head;

    for (; copy; copy = copy->next) {
        if (already_subscribed(copy->team_tab, uuid)) {
            //Send to user: user_id + user_name + user_status
        }
    }
}

int subscribed_cmd(myteams_t *teams, client_t *client, char **arg)
{
    uuid_t temp;
    team_t *team_to_look;

    if (!client->is_connected)
        return (reply_unauthorized(client));
    if (!arg || double_array_size(arg) != 2) {
        list_teams_subscribed(client->team_tab);
        return (0);
    }
    uuid_parse(arg[0], temp);
    team_to_look = get_team_by_uuid(teams->team_head, temp);
    if (!team_to_look) {
        //Error unknown team
        return (0);
    } else if (!already_subscribed(client->team_tab, temp)) {
        //Error not subscribed unauthorized
        return (0);
    }
    list_users_subscribed(teams->client_head, temp);
    return (0);
}