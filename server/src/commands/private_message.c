/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"
#include "structs.h"

void process_message(client_t *client, client_t *searched)
{
    char *reply = NULL;
    message_t *copy = client->message_head;
    char timestamp[64];
    char uuid[36];

    for (; copy; copy = copy->next) {
        if (uuid_compare(searched->user_uuid, copy->sender) == 0 ||
            uuid_compare(searched->user_uuid, copy->receiver) == 0) {
            uuid_unparse(copy->sender, uuid);
            sprintf(timestamp, "%ld", copy->timestamp);
            reply = format_response(4, LIST_PM, uuid, timestamp, copy->body);
            insert_reply(&client->replies, reply);
            free(reply);
        }
    }
}

int specific_message_cmd(myteams_t *teams, client_t *client, char **input)
{
    client_t *searched;
    uuid_t temp;

    if (!client->is_connected)
        return (reply_unauthorized(client));
    else if (double_array_size(input) != 2)
        return (bad_cmd_parameters(client, input[0]));
    if (uuid_parse(input[1], temp) == -1)
        return (reply_unknown_user(client, input[1]));
    searched = get_client_by_uuid(teams->client_head, temp);
    if (!searched)
        return (reply_unknown_user(client, input[1]));
    else
        process_message(client, searched);
    return (0);
}