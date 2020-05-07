/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

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

void use_team(myteams_t *teams, client_t *client, char **input)
{
    uuid_t uuid;
    team_t *team;

    if (uuid_parse(input[1], uuid) == -1)
        //Error bad uuid
        return;
    team = get_team_by_uuid(teams->team_head, uuid);
    if (!team)
        //Error: unknown team
        return;
    uuid_copy(client->team_chosen, uuid);
    uuid_clear(client->channel_chosen);
    uuid_clear(client->thread_chosen);
    client->depth = TEAM;
}

void use_channel(myteams_t *teams, client_t *client, char **input)
{
    uuid_t team_uuid;
    uuid_t channel_uuid;
    team_t *team;
    channel_t *channel;

    if (uuid_parse(input[1], team_uuid) == -1)
        //Error bad uuid
        return;
    team = get_team_by_uuid(teams->team_head, team_uuid);
    if (!team)
        //Error : unknown team
        return;
    if (uuid_parse(input[2], channel_uuid) == -1)
        //Error in channel
        return;
    channel = get_channel_by_uuid(team->channel_head, channel_uuid);
    if (!channel)
        //Error : unknow team
        return;
    uuid_copy(client->team_chosen, team_uuid);
    uuid_copy(client->channel_chosen, channel_uuid);
    uuid_clear(client->thread_chosen);
    client->depth = CHANNEL;
}

void use_thread(myteams_t *teams, client_t *client, char **input)
{
    uuid_t team_uuid;
    uuid_t channel_uuid;
    uuid_t thread_uuid;
    team_t *team;
    channel_t *channel;
    thread_t *thread;

    if (uuid_parse(input[1], team_uuid) == -1)
        //Error bad uuid
        return;
    team = get_team_by_uuid(teams->team_head, team_uuid);
    if (!team)
        //Error : unknown team
        return;
    if (uuid_parse(input[2], channel_uuid) == -1)
        //Error in channel
        return;
    channel = get_channel_by_uuid(team->channel_head, channel_uuid);
    if (!channel)
        //Error : unknow channel
        return;
    if (uuid_parse(input[3], thread_uuid) == -1)
        //Error in channel
        return;
    thread = get_thread_by_uuid(channel->thread_head, thread_uuid);
    if (!thread)
        //Error : unknown thread
        return;
    uuid_copy(client->team_chosen, team_uuid);
    uuid_copy(client->channel_chosen, channel_uuid);
    uuid_copy(client->thread_chosen, thread_uuid);
    client->depth = THREAD;
}

void use_cmd(myteams_t *teams, client_t *client, char **input)
{
    int nbr_arg;

    if (client->is_connected == false) {
        not_logged_in(client);
        return;
    }
    nbr_arg = double_array_size(input);
    switch (nbr_arg) {
        case 1:
            use_undefined(teams, client);
            break;
        case 2:
            use_team(teams, client, input);
            break;
        case 3:
            use_channel(teams, client, input);
            break;
        case 4:
            use_thread(teams, client, input);
            break;
        default:
            //Error too much args
            return;
    }
}