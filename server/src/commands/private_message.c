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

int specific_message_cmd(myteams_t *teams, client_t *client, char **input)
{
    client_t *searched;
    uuid_t temp;
    message_t *copy = client->message_head;
    char *reply;
    char uuid[36];
    char timestamp[64];

    if (client->is_connected == false)
        return reply_unauthorized(client);
    if (double_array_size(input) != 2)
        //Error bad args
        return 1;
    if (uuid_parse(input[1], temp) == -1)
        return reply_unknown_user(client, input[1]);
    searched = get_client_by_uuid(teams->client_head, temp);
    if (!searched)
        return reply_unknown_user(client, input[1]);
    for (; copy; copy = copy->next) {
        if (uuid_compare(client->user_uuid, copy->sender) == 0 ||
            uuid_compare(client->user_uuid, copy->receiver) == 0) {
            uuid_unparse(copy->sender, uuid);
            sprintf(timestamp, "%ld", copy->timestamp);
            reply = format_response(4, LIST_PM, uuid, timestamp, copy->body);
            insert_reply(&client->replies, reply);
            free(reply);
        }
    }
    return 0;
}