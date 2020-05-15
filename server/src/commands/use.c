/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include "prototypes.h"
#include "clients_storage.h"
#include "structs.h"

void use_undefined(myteams_t *teams, client_t *client)
{
    (void)(teams);
    uuid_clear(client->team_chosen);
    uuid_clear(client->channel_chosen);
    uuid_clear(client->thread_chosen);
    client->depth = UNDEFINED;
}

int use_team(myteams_t *teams, client_t *client, char **input)
{
    uuid_t uuid;
    team_t *team;

    if (uuid_parse(input[1], uuid) == -1)
        return (bad_cmd_parameters(client, input[0]));
    team = get_team_by_uuid(teams->team_head, uuid);
    if (!team)
        return (reply_unknown_team(client, input[1]));
    uuid_copy(client->team_chosen, uuid);
    uuid_clear(client->channel_chosen);
    uuid_clear(client->thread_chosen);
    client->depth = TEAM;
    return (0);
}

int use_channel(myteams_t *teams, client_t *client, char **input)
{
    uuid_t team_uuid;
    uuid_t channel_uuid;
    team_t *team;
    channel_t *channel;

    if (uuid_parse(input[1], team_uuid) == -1)
        return (bad_cmd_parameters(client, input[0]));
    team = get_team_by_uuid(teams->team_head, team_uuid);
    if (!team)
        return (reply_unknown_team(client, input[1]));
    else if (uuid_parse(input[2], channel_uuid) == -1)
        return (reply_unknown_channel(client, input[2]));
    channel = get_channel_by_uuid(team->channel_head, channel_uuid);
    if (!channel)
        return (reply_unknown_channel(client, input[2]));
    uuid_copy(client->team_chosen, team_uuid);
    uuid_copy(client->channel_chosen, channel_uuid);
    uuid_clear(client->thread_chosen);
    client->depth = CHANNEL;
    return (0);
}

int use_cmd(myteams_t *teams, client_t *client, char **input)
{
    if (!client->is_connected)
        return (reply_unauthorized(client));
    switch (double_array_size(input)) {
        case 1:
            printf("Switched to the undefined\n");
            use_undefined(teams, client);
            break;
        case 2:
            printf("Switched to the team\n");
            use_team(teams, client, input);
            break;
        case 3:
            printf("Switched to the channel\n");
            use_channel(teams, client, input);
            break;
        case 4:
            printf("Switched to the thread\n");
            use_thread(teams, client, input);
            break;
        default:
            return (bad_cmd_parameters(client, input[0]));
    }
    return (0);
}