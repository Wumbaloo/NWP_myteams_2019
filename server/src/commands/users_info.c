/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

int specific_user_cmd(myteams_t *teams, client_t *client, char  **input)
{
    client_t *searched;
    uuid_t temp;
    char *reply;

    if (client->is_connected == false)
        return reply_unauthorized(client);
    if (!input[1])
        //Not enough arg
        return 1;
    uuid_parse(input[1], temp);
    searched = get_client_by_uuid(teams->client_head, temp);
    if (!searched)
        return reply_unknown_user(client, input[1]);
    reply = format_response(4, INFO_USER, input[1], searched->user_name,
        searched->is_connected ? "1" : "0");
    insert_reply(&client->replies, reply);
    free(reply);
    return 0;
}

int users_cmd(myteams_t *teams, client_t *client, char **input)
{
    sub_list_t *banned;
    client_t *copy = teams->client_head;
    char *reply;
    char uuid[36];

    (void)(teams);
    (void)(input);
    if (client->is_connected == false)
        return (reply_unauthorized(client));
    for (; copy; copy = copy->next) {
        if (already_subscribed(banned, copy->user_uuid))
            continue;
        uuid_unparse(copy->user_uuid, uuid);
        reply = format_response(4, LIST_USERS, uuid, copy->user_name, copy->is_connected ? "1" : "0");
        insert_reply(&client->replies, reply);
        insert_in_sub_list(&banned, copy->user_uuid);
        free(reply);
    }
    return (1);
}
