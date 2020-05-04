/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

void specific_message_cmd(myteams_t *teams, client_t *client, void *arg)
{
    client_t *searched;
    uuid_t temp;
    message_t *copy = client->message_head;

    if (client->is_connected == false) {
        //Error not logged
        return;
    }
    uuid_parse(arg, temp);
    searched = get_client_by_uuid(teams->client_head, temp);
    if (!searched) {
        //Error unknown user
        return;
    }
    while (copy) {
        if (uuid_compare(client->user_uuid, copy->sender) == 0 ||
        uuid_compare(client->user_uuid, copy->receiver)) {
            //Send to user: sender_id + timestamp + message
        }
        copy = copy->next;
    }
}