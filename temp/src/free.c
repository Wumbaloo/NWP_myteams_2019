/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "ftp.h"

void free_client(client_t *client)
{
    if (client) {
        if (client->folder_path)
            free(client->folder_path);
        free(client);
    }
}