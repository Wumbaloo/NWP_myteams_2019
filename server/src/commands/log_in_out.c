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

void answer_client_login(client_t *client, char uuid[36], int code)
{
    size_t len = snprintf(NULL, 0, "%d %s", code, uuid);
    char *msg = malloc(sizeof(char) * (len + 1));

    if (!msg)
        return;
    sprintf(msg, "%d %s %s", code, uuid, client->user_name);
    client->reply = msg;
}

void login_cmd(myteams_t *teams, client_t *client, char **input)
{
    char uuid[36];
    client_t *temp = get_client_by_username(teams->client_head, input[1]);

    if (!input)
        return;
    //User déjà connecté
    if (temp && temp->is_connected == true)
        duplicate_client(temp, client);
    //User reprend sa session
    else if (temp && temp->is_connected == false)
        temp->is_connected = true;
    //User : première arrivée
    else {
        uuid_generate(client->user_uuid);
        memcpy(client->user_name, input[1], DEFAULT_NAME_LENGTH);
        client->is_connected = true;
    }
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_logged_in(uuid);
    answer_client_login(client, uuid, 230);
}

void logout_cmd(myteams_t *teams, client_t *client, char **input)
{
    char uuid[36];

    (void)(input);
    if (client->is_connected == false) {
        //Error not logged in
        return;
    }
    client->is_connected = false;
    uuid_clear(client->use_position);
    client->depth = UNDEFINED;
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_logged_out(uuid);
    answer_client_login(client, uuid, 231);
}