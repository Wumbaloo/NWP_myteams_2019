/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <string.h>
#include <stdio.h>
#include <zconf.h>
#include "ftp.h"
#include "prototypes.h"

void no_operation(ftp_t *ftp, int fd)
{
    client_t *client = get_client(ftp->firstnode, fd);

    if (!client->is_connected) {
        client->reply = strdup(NOT_CONNECTED);
        return;
    }
    client->reply = strdup(NOOP);
}

void quit(ftp_t *ftp, int fd)
{
    if (FD_ISSET(fd, &ftp->writeset))
        dprintf(fd, QUIT);
    remove_client(ftp->firstnode, fd);
    close(fd);
    ftp->clients[ftp->act_idx] = 0;
}

void print_help(ftp_t *ftp, int fd)
{
    client_t *client = get_client(ftp->firstnode, fd);

    if (!client->is_connected) {
        client->reply = strdup(NOT_CONNECTED);
        return;
    }
    client->reply = strdup(
        "214 The following commands are recognized.\n"
        "CDUP CWD DELE HELP LIST NOOP PASS PASV PORT PWD QUIT RETR STOR USER"
        "\n214 Help OK.");
}