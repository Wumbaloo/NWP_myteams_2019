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

void subscribed_cmd(myteams_t *teams, client_t *client, void *arg)
{
    uuid_t temp;
    team_t *team_to_look;

    if (client->is_connected == false) {
        //Error not logged
        return;
    }
    if (!arg) {
        list_teams_subscribed(client->team_tab);
        return;
    }
    uuid_parse(arg, temp);
    team_to_look = get_team_by_uuid(teams->team_head, temp);
    if (!team_to_look) {
        //Error unknown team
        return;
    } else if (!already_subscribed(client->team_tab, temp)) {
        //Error not subscribed unauthorized
        return;
    }
    list_users_subscribed(teams->client_head, temp);
}