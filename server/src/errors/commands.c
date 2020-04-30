/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Commands error handling
*/

#include <string.h>
#include "prototypes.h"
#include "structs.h"
#include "teams.h"

void bad_command(teams_t *teams, int fd)
{
    client_t *client = get_client(teams->client_head, fd);

    if (!client->is_connected) {
        client->reply = strdup(NOT_CONNECTED);
        return;
    }
    client->reply = strdup(BAD_CMD);
}