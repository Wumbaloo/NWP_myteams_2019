/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Commands error handling
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

void not_logged_in(client_t *client)
{
    client->reply = strdup("600 Not logged in");
}

void bad_command(client_t *client, char *cmd)
{
    size_t len;
    char *msg = NULL;

    if (!cmd) {
        return;
    } else {
        len = snprintf(NULL, 0, "%d %s", 601, cmd);
        msg = malloc(sizeof(char) * (len + 1));
        if (!msg)
            perror_exit("malloc", 84);
        sprintf(msg, "%d %s", 601, cmd);
        client->reply = msg;
    }
}

void bad_cmd_parameters(client_t *client, char *cmd)
{
    int code = 602;
    size_t len = snprintf(NULL, 0, "%d %s", code, cmd);
    char *msg = malloc(sizeof(char) * (len + 1));

    if (!msg)
        return;
    sprintf(msg, "%d %s", code, cmd);
    client->reply = msg;
}