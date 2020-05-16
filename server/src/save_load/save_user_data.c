/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include "structs.h"

void save_sub_list(char *list_type, sub_list_t *sub_list, int file)
{
    sub_list_t *tmp = sub_list;
    char uuid[36];

    dprintf(file, "%s ", list_type);
    for (; tmp; tmp = tmp->next) {
        uuid_unparse(tmp->uuid, uuid);
        dprintf(file, "\"%s\" ", uuid);
    }
}

void save_private_messages(message_t *messages, int file, char uuid[36])
{
    message_t *tmp = messages;
    char sender_uuid[36];
    char receiver_uuid[36];

    for (; tmp; tmp = tmp->next) {
        uuid_unparse(tmp->sender, sender_uuid);
        uuid_unparse(tmp->receiver, receiver_uuid);
        dprintf(file, "PRIVATE_MESSAGE \"%ld\" \"%s\" \"%s\" \"%s\" \"%s\"\n",
            tmp->timestamp, sender_uuid, receiver_uuid, tmp->body, uuid);
    }
}

void save_users(myteams_t *teams, int file)
{
    client_t *tmp = teams->client_head;
    char uuid[36];

    while (tmp) {
        uuid_unparse(tmp->user_uuid, uuid);
        dprintf(file, "USER \"%s\" \"%s\" ", tmp->user_name, uuid);
        save_sub_list("TEAM_SUB", tmp->team_tab, file);
        save_sub_list("CHANNEL_SUB", tmp->channel_tab, file);
        save_sub_list("CHANNEL_SUB", tmp->channel_tab, file);
        dprintf(file, "\n");
        save_private_messages(tmp->message_head, file, uuid);
        tmp = tmp->next;
    }
}