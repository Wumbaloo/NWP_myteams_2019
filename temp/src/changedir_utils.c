/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include "ftp.h"
#include "prototypes.h"

char *get_new_cat_path(char *first_part, char *second_part)
{
    char *new_path = my_strcat(first_part, "/");

    new_path = my_strcat(new_path, second_part);
    return new_path;
}

void no_arg_on_cwd(ftp_t *ftp, int fd)
{
    client_t *client = get_client(ftp->firstnode, fd);

    if (!client->is_connected) {
        client->reply = strdup(NOT_CONNECTED);
        return;
    }
    client->reply = strdup(FAILED_CHANGEDIR);
}

int try_from_root(char *path)
{
    DIR *temp = opendir(path);

    if (temp == NULL)
        return 1;
    closedir(temp);
    return 0;
}

int try_cat(client_t *client, char *path)
{
    char *new_path = get_new_cat_path(client->folder_path, path);
    DIR *temp = opendir(new_path);

    if (temp == NULL) {
        free(new_path);
        return 1;
    }
    free(new_path);
    closedir(temp);
    return 0;
}