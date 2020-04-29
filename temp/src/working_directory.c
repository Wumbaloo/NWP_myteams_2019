/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ftp.h"
#include "prototypes.h"

void print_working_directory(ftp_t *ftp, int fd)
{
    client_t *client = get_client(ftp->firstnode, fd);

    if (!client->is_connected) {
        client->reply = strdup(NOT_CONNECTED);
        return;
    }
    client->reply = malloc(sizeof(char) * (10 + strlen(client->folder_path)));
    sprintf(client->reply, "257 \"%s\"", client->folder_path);
}

void execute_switch(client_t *client, DIR *new_dir, char *path)
{
    char buf[PATH_MAX];

    closedir(client->current_directory);
    client->current_directory = new_dir;
    realpath(path, buf);
    free(client->folder_path);
    client->folder_path = strdup(buf);
}

void change_directory(ftp_t *ftp, int fd, char *buffer)
{
    client_t *client = get_client(ftp->firstnode, fd);
    char *token = NULL;
    DIR *temp_dir = NULL;
    char *new_path = NULL;

    if (!client->is_connected) {
        client->reply = strdup(NOT_CONNECTED);
        return;
    }
    token = get_argument(buffer);
    if (!try_from_root(token)) {
        temp_dir = opendir(token);
        execute_switch(client, temp_dir, token);
    } else if (!try_cat(client, token)) {
        new_path = get_new_cat_path(client->folder_path, token);
        temp_dir = opendir(new_path);
        execute_switch(client, temp_dir, new_path);
        free(new_path);
    } else {
        client->reply = strdup(FAILED_CHANGEDIR);
        return;
    }
    client->reply = strdup(OK_CHANGEDIR);
}

void change_dir_to_parent(ftp_t *ftp, int fd)
{
    client_t *client = get_client(ftp->firstnode, fd);
    char *new_path = NULL;
    DIR *temp_dir = NULL;

    if (!client->is_connected) {
        client->reply = strdup(NOT_CONNECTED);
        return;
    }
    new_path = my_strcat(client->folder_path, "/..");
    temp_dir = opendir(new_path);
    if (temp_dir == NULL) {
        client->reply = strdup(FAILED_CHANGEDIR);
        free(new_path);
        return;
    }
    execute_switch(client, temp_dir, new_path);
    client->reply = strdup(OK_CHANGEDIR);
}