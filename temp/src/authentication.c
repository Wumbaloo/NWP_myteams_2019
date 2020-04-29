/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <string.h>
#include <stdio.h>
#include "ftp.h"
#include "prototypes.h"

void check_connection(client_t *client)
{
    if (client->username == TRUE && client->password == TRUE) {
        client->reply = strdup(GOOD_LOGIN);
        client->is_connected = true;
    } else {
        client->reply = strdup(BAD_LOGIN);
        client->is_connected = false;
        client->username = UNDEFINED;
        client->password = UNDEFINED;
    }
}

void try_password(ftp_t *ftp, int fd, char *buffer)
{
    client_t *client = get_client(ftp->firstnode, fd);

    if (client->is_connected) {
        client->reply = strdup(ALREADY_LOGGED);
        return;
    } else if (client->username == UNDEFINED) {
        client->reply = strdup(NO_USER);
        return;
    }
    buffer[strlen(buffer) - 2] = '\0';
    client->password = (strlen(buffer) == 5) ? TRUE : FALSE;
    check_connection(client);
}

void try_username(ftp_t *ftp, int fd, char *buffer)
{
    client_t *client = get_client(ftp->firstnode, fd);
    char *token = NULL;

    if (client->is_connected) {
        client->reply = strdup(CHANGE_USER);
        return;
    }
    token = get_argument(buffer);
    client->username = (strcasecmp(token, USER) == 0) ? TRUE : FALSE;
    client->reply = strdup(NEED_PASSWORD);
}