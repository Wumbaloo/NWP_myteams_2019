/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <unistd.h>
#include <stdio.h>
#include "ftp.h"
#include "prototypes.h"

int accept_connection(int server_socket)
{
    int client_socket;
    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);

    client_socket = accept(server_socket, (struct sockaddr *)&cli_addr,
        &cli_len);
    return client_socket;
}

void reset_update_set(ftp_t *ftp)
{
    int act_fd;

    FD_ZERO(&ftp->readset);
    FD_ZERO(&ftp->writeset);
    FD_SET(ftp->server->control_socket, &ftp->readset);
    ftp->maxfd = ftp->server->control_socket;
    for (int i = 0; i < CLIENTS_MAX; i++) {
        act_fd = ftp->clients[i];
        if (act_fd > 0) {
            FD_SET(act_fd, &ftp->readset);
            FD_SET(act_fd, &ftp->writeset);
        }
        if (act_fd > ftp->maxfd)
            ftp->maxfd = act_fd;
    }
}

void connection_received(ftp_t *ftp)
{
    int new_socket = accept_connection(ftp->server->control_socket);
    int full_connected = 0;

    for (int i = 0; i < CLIENTS_MAX; i++) {
        if (ftp->clients[i] == 0) {
            ftp->clients[i] = new_socket;
            dprintf(new_socket, "%s\r\n", HELLO);
            insert_client(ftp->firstnode, new_socket, ftp->default_path);
            break;
        } else
            full_connected++;
    }
    if (full_connected == CLIENTS_MAX) {
        write(new_socket,
            "Sorry, the maximum of connections authorized is reached\n", 56);
        close(new_socket);
    }
}

void check_for_instructions(ftp_t *ftp)
{
    char buffer[1024] = {0};
    int act_fd;

    for (int i = 0; i < CLIENTS_MAX; i++) {
        act_fd = ftp->clients[i];
        if (FD_ISSET(act_fd, &ftp->readset)) {
            ftp->act_idx = i;
            if (read(act_fd, buffer, 1024) == 0) {
                remove_client(ftp->firstnode, act_fd);
                close(act_fd);
                ftp->clients[i] = 0;
            } else {
                manage_connection(ftp, act_fd, buffer);
                send_replies(ftp->firstnode, ftp->writeset);
            }
        }
    }
}