/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "prototypes.h"
#include "logging_server.h"

void login_cmd(myteams_t *teams, client_t *client, void *arg)
{
    char uuid[36];
    client_t *temp = get_client_by_username(teams->client_head, arg);

    //User déjà connecté
    if (temp && temp->is_connected == true)
        duplicate_client(temp, client);
    //User reprend sa session
    else if (temp && temp->is_connected == false)
        temp->is_connected = true;
    //User : première arrivée
    else {
        uuid_generate(client->user_uuid);
        memcpy(client->user_name, arg, DEFAULT_NAME_LENGTH);
        client->is_connected = true;
    }
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_logged_in(uuid);
    //Envoyer réponse au client
}

void logout_cmd(myteams_t *teams, client_t *client, void *arg)
{
    char uuid[36];

    (void)(arg);
    if (client->is_connected == false)
    {
        //Error not logged in
        return;
    }
    client->is_connected = false;
    uuid_clear(client->use_position);
    client->depth = UNDEFINED;
    close(client->fd);
    teams->clients[teams->act_idx] = 0;
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_logged_out(uuid);
    //Envoyer réponse au client
}