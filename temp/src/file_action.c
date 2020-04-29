/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <string.h>
#include "ftp.h"
#include "prototypes.h"

void delete_file(ftp_t *ftp, int fd, char *buffer)
{
    client_t *client = get_client(ftp->firstnode, fd);
    char *to_delete = NULL;
    char *from_path = NULL;

    if (!client->is_connected) {
        client->reply = strdup(NOT_CONNECTED);
        return ;
    }
    to_delete = get_argument(buffer);
    if (!remove(to_delete)) {
        client->reply = strdup(OK_DELE);
        return;
    }
    from_path = my_strcat(client->folder_path, "/");
    from_path = my_strcat(from_path, to_delete);
    if (!remove(from_path)) {
        client->reply = strdup(OK_DELE);
        return;
    }
    client->reply = strdup(FAILED_DELE);
}