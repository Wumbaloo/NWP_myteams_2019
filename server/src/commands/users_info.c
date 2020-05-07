/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

void specific_user_cmd(myteams_t *teams, client_t *client, char  **input)
{
    client_t *searched;
    uuid_t temp;

    if (client->is_connected == false) {
        not_logged_in(client);
        return;
    }
    if (!input[1])
        //Not enough arg
        return;
    uuid_parse(input[1], temp);
    searched = get_client_by_uuid(teams->client_head, temp);
    if (!searched) {
        //Error User Unknown
        return;
    }
    //Send to the user : uuid + user_name + user_status
}

void users_cmd(myteams_t *teams, client_t *client, char **input)
{
    int size = nbr_clients(teams->client_head);
    uuid_t *banned;
    client_t *copy = teams->client_head;

    (void)(teams);
    (void)(input);
    if (client->is_connected == false) {
        not_logged_in(client);
        return;
    }
    banned = malloc(sizeof(uuid_t) * (size));
    if (!banned)
        perror_exit("malloc", 84);
    for (int i = 0; i < size; i++) {
        for (int idx = 0; idx < i; idx++)
            if (uuid_compare(banned[idx], copy->user_uuid) == 0)
                continue;
        //Send user uuid (as char[]) + user_name + status (connected or not as int)
        uuid_copy(banned[i], copy->user_uuid);
        copy = copy->next;
    }
    free(banned);
}
