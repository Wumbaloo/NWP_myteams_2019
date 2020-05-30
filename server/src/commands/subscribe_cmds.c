/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Where subscribe methods are handled
*/

#include <stdio.h>
#include "logging_server.h"
#include "structs.h"
#include "prototypes.h"

void unsubscribe_cmd_sequel(myteams_t *teams, client_t *client, uuid_t temp,
    team_t *to_unsubscribe)
{
    client_t *client_tmp = teams->client_head;

    for (; client_tmp; client_tmp = client_tmp->next) {
        if (uuid_compare(client->user_uuid, client_tmp->user_uuid) == 0) {
            remove_in_sub_list(client_tmp->team_tab, temp);
            unsubscribe_from_sub_channels(client_tmp->channel_tab,
                to_unsubscribe);
        }
    }
}

int unsubscribe_cmd(myteams_t *teams, client_t *client, char **input)
{
    team_t *to_unsubscribe;
    uuid_t temp;
    char uuid[36];

    if (!client->is_connected)
        return (reply_unauthorized(client));
    else if (!input[1])
        return (bad_cmd_parameters(client, input[0]));
    if (uuid_parse(input[1], temp) != 0)
        return (reply_unknown_team(client, input[1]));
    to_unsubscribe = get_team_by_uuid(teams->team_head, temp);
    if (!to_unsubscribe)
        return (reply_unknown_team(client, input[1]));
    else if (already_subscribed(client->team_tab, temp) == false)
        return (reply_unauthorized(client));
    unsubscribe_cmd_sequel(teams, client, temp, to_unsubscribe);
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_leave_a_team(input[1], uuid);
    broadcast_unsubscription(client, input[1]);
    return (0);
}

int uuid_tab_size(sub_list_t *tab)
{
    sub_list_t *copy = tab;
    int i = 0;
    for (; copy; copy = copy->next)
        i++;
    return i;
}

void subscribe_cmd_sequel(myteams_t *teams, client_t *client, uuid_t temp,
    team_t *to_subscribe)
{
    client_t *client_tmp = teams->client_head;

    for (; client_tmp; client_tmp = client_tmp->next) {
        if (uuid_compare(client->user_uuid, client_tmp->user_uuid) == 0) {
            insert_in_sub_list(&client_tmp->team_tab, temp);
            subscribe_to_subchannels(&client->channel_tab, to_subscribe);
            printf("Client subscribed to %d channels\n", uuid_tab_size(client->channel_tab));
        }
    }
}

int subscribe_cmd(myteams_t *teams, client_t *client, char **input)
{
    team_t *to_subscribe;
    uuid_t temp;
    char uuid[36];

    if (!client->is_connected)
        return (reply_unauthorized(client));
    else if (!input[1])
        return (bad_cmd_parameters(client, input[0]));
    if (uuid_parse(input[1], temp) == -1)
        return (reply_unknown_team(client, input[1]));
    to_subscribe = get_team_by_uuid(teams->team_head, temp);
    if (!to_subscribe)
        return (reply_unknown_team(client, input[1]));
    else if (already_subscribed(client->team_tab, temp))
        return (reply_resource_already_exists(client));
    subscribe_cmd_sequel(teams, client, temp, to_subscribe);
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_join_a_team(input[1], uuid);
    broadcast_subscription(client, input[1]);
    return (0);
}
