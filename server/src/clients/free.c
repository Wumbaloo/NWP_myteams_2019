/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Where clients are free
*/

#include <stdlib.h>
#include "structs.h"

void free_client(client_t *client)
{
    if (client) {
        if (client->folder_path)
            free(client->folder_path);
        free(client);
    }
}