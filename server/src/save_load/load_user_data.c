/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <string.h>
#include <stdlib.h>
#include "logging_server.h"
#include <stdio.h>
#include "prototypes.h"

int get_sub_pos(char **array, char *sub_searched)
{
    int idx = 0;

    for (; array[idx]; idx++)
        if (strcmp(array[idx], sub_searched) == 0)
            return idx;
    return 0;
}

void re_subscribe(char **array, client_t *client)
{
    uuid_t uuid;

    for (int i = get_sub_pos(array, "TEAM_SUB") + 1; strcmp(array[i], "CHANNEL_SUB"); i++) {
        uuid_parse(array[i], uuid);
        insert_in_sub_list(&client->team_tab, uuid);
    }
    for (int i = get_sub_pos(array, "CHANNEL_SUB") + 1; strcmp(array[i], "THREAD_SUB"); i++) {
        uuid_parse(array[i], uuid);
        insert_in_sub_list(&client->channel_tab, uuid);
    }
    for (int i = get_sub_pos(array, "THREAD_SUB") + 1; array[i]; i++) {
        uuid_parse(array[i], uuid);
        insert_in_sub_list(&client->thread_tab, uuid);
    }
}

void load_user(myteams_t *teams, char **array)
{
    uuid_t uuid;
    client_t *client;

    insert_client(&teams->client_head, -21);
    uuid_parse(array[1], uuid);
    client = get_client_by_fd(teams->client_head, -21);
    for (int i = 0; array[0][i] && i < DEFAULT_NAME_LENGTH; i++)
        client->user_name[i] = array[0][i];
    uuid_copy(client->user_uuid, uuid);
    re_subscribe(array, client);
    client->fd = -1;
    server_event_user_loaded(array[4], client->user_name);
}

void load_private_message(myteams_t *teams, char **array)
{
    client_t *client;
    message_t *message;
    uuid_t uuid;
    uuid_t uuid_tmp;
    time_t timestamp = strtol(array[0], NULL, 10);

    uuid_parse(array[4], uuid);
    client = get_client_by_uuid(teams->client_head, uuid);
    uuid_parse(array[1], uuid);
    uuid_parse(array[2], uuid);
    insert_message(&client->message_head, uuid, uuid_tmp, array[3]);
    message = get_message(client->message_head, uuid, uuid_tmp, array[3]);
    message->timestamp = timestamp;
}