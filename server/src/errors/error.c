/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>
#include "ftp.h"
#include "prototypes.h"

int return_with_msg(char *msg, int return_value)
{
    fprintf(stderr, "%s\n", msg);
    return (return_value);
}

void bad_command(ftp_t *ftp, int fd)
{
    client_t *client = get_client(ftp->firstnode, fd);

    if (!client->is_connected) {
        client->reply = strdup(NOT_CONNECTED);
        return;
    }
    client->reply = strdup(BAD_CMD);
}

int check_path(char *path)
{
    DIR *directory = opendir(path);

    if (directory == NULL)
        return return_with_msg("Unable to open the specified path/folder", 1);
    closedir(directory);
    return (0);
}

int error_handling(int ac, char **av)
{
    if (ac != 2)
        return (return_with_msg("The program should have only 1 argument.", 1));
    if (!strcmp(av[1], "-help"))
        return (0);
    if (strlen(av[1]) == 0)
        return (return_with_msg("Arguments can't be empty", 1));
    for (int i = 0; av[1][i]; i++) {
        if (!isdigit(av[1][i]))
            return (return_with_msg("The port should only be composed of digits", 1));
    }
    if (atoi(av[1]) > 65635)
        return (return_with_msg("The port should be included in [1-65535]", 1));
    if (check_path(av[2]))
        return (1);
    return (0);
}