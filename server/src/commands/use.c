/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include "prototypes.h"
#include "clients_storage.h"
#include "structs.h"

void use_undefined(team_t *head, client_t *client, uuid_t uuid)
{
    team_t *team = get_team_by_uuid(head, uuid);

    if (!team) {
        //Error unknown team
        return;
    }
}

void use_team()
{
}

void use_channel()
{
}

void use_thread()
{
}

void use_cmd(myteams_t *teams, client_t *client, void *arg)
{
    uuid_t uuid;

    if (client->is_connected == false) {
        //Error not logged
        return;
    }
    if (!arg) {
        uuid_clear(client->use_position);
        client->depth = UNDEFINED;
        return;
    } else
        uuid_parse(arg, uuid);
    switch (client->depth) {
        case UNDEFINED:
            use_undefined(teams->team_head, client, uuid);
            break;
        case TEAM:
            use_team();
        case CHANNEL:
            use_channel();
        case THREAD:
            use_thread();
    }
    console_log(NULL, "NOT FINISHED", ERROR, NULL);
}