/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

int check_error_specific_msg(myteams_t *teams, client_t *client, char **input)
{
    uuid_t temp;
    client_t *searched;

    if (client->is_connected == false) {
        not_logged_in(client);
        return (1);
    }
    if (double_array_size(input) != 2) {
        //Error bad args
        return (1);
    }
    if (uuid_parse(input[1], temp) == -1) {
        //Error bad uuid
        return (1);
    }
    searched = get_client_by_uuid(teams->client_head, temp);
    if (!searched) {
        //Error unknown user
        return (1);
    }
    return (0);
}

void specific_message_cmd(myteams_t *teams, client_t *client, char **input)
{
    message_t *copy = client->message_head;

    if (check_error_specific_msg(teams, client, input) > 0)
        return;
    while (copy) {
        if (uuid_compare(client->user_uuid, copy->sender) == 0 ||
        uuid_compare(client->user_uuid, copy->receiver)) {
            //Send to user: sender_id + timestamp + message
        }
        copy = copy->next;
    }
}