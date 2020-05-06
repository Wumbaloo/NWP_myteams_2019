/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include "prototypes.h"
#include "structs.h"

void send_and_notify(client_t *from, client_t *receiver, char *msg, client_t *head)
{
    client_t *copy = head;

    for (; copy; copy = copy->next) {
        if (uuid_compare(from->user_uuid, copy->user_uuid) == 0)
            //Set the reply
            insert_message(&from->message_head, from->user_uuid, receiver->user_uuid, msg);
        else if (uuid_compare(receiver->user_uuid, copy->user_uuid) == 0)
            //Set the reply
            insert_message(&receiver->message_head, from->user_uuid, receiver->user_uuid, msg);
    }
}

void send_cmd(myteams_t *teams, client_t *from, char **input)
{
    uuid_t temp;
    client_t *receiver;

    if (from->is_connected == false)
        //Error not logged
        return;
    else if (double_array_size(input) != 3)
        //Bad number of arguments
        return;
    uuid_parse(input[1], temp);
    receiver = get_client_by_uuid(teams->client_head, temp);
    if (!receiver)
        //Error unknown user
        return;
    send_and_notify(from, receiver, input[2], teams->client_head);
    //Tell user message have been received BY THE SERVER
}