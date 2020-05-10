/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <stdio.h>
#include "logging_server.h"
#include "prototypes.h"
#include "macros.h"
#include "structs.h"

void send_and_notify(client_t *client, client_t *receiver, char *msg,
    client_t *head
)
{
    client_t *copy = head;
    char sender_uuid[36];
    char *reply;

    uuid_unparse(client->user_uuid, sender_uuid);
    reply = format_response(3, PM_RECEIVED, sender_uuid, msg);

    for (; copy; copy = copy->next) {
        if (uuid_compare(copy->user_uuid, receiver->user_uuid) == 0) {
            insert_message(&copy->message_head, client->user_uuid,
                receiver->user_uuid, msg);
            insert_reply(&copy->replies, reply);
        } else if (uuid_compare(copy->user_uuid, client->user_uuid) == 0) {
            insert_message(&copy->message_head, client->user_uuid,
                receiver->user_uuid, msg);
        }
    }
    free(reply);
}

int send_cmd(myteams_t *teams, client_t *from, char **input)
{
    uuid_t temp;
    client_t *receiver;
    char sender_uuid[36];

    if (!from->is_connected)
        return (reply_unauthorized(from));
    else if (double_array_size(input) != 3)
        return (bad_cmd_parameters(from, input[0]));
    if (uuid_parse(input[1], temp) != 0)
        return (reply_unknown_user(from, input[1]));
    receiver = get_client_by_uuid(teams->client_head, temp);
    if (!receiver)
        return (reply_unknown_user(from, input[1]));
    uuid_unparse(from->user_uuid, sender_uuid);
    server_event_private_message_sended(sender_uuid, input[1], input[2]);
    send_and_notify(from, receiver, input[2], teams->client_head);
    return 0;
}