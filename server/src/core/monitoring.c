/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Server monitoring source file
*/

#include <unistd.h>
#include <stdio.h>
#include "teams.h"
#include "prototypes.h"
#include "structs.h"

int accept_connection(int server_socket)
{
    int client_socket;
    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);

    client_socket = accept(server_socket, (struct sockaddr *) &cli_addr,
        &cli_len);
    return (client_socket);
}

void reset_update_set(teams_t *teams)
{
    int act_fd;

    FD_ZERO(&teams->readset);
    FD_ZERO(&teams->writeset);
    FD_SET(teams->server->control_socket, &teams->readset);
    teams->maxfd = teams->server->control_socket;
    for (int i = 0; i < CLIENTS_MAX; i++) {
        act_fd = teams->clients[i];
        if (act_fd > 0) {
            FD_SET(act_fd, &teams->readset);
            FD_SET(act_fd, &teams->writeset);
        }
        if (act_fd > teams->maxfd)
            teams->maxfd = act_fd;
    }
}

void connection_received(teams_t *teams)
{
    int new_socket = accept_connection(teams->server->control_socket);
    int full_connected = 0;

    if (new_socket < 0) {
        perror("accept");
        return;
    }
    for (int i = 0; i < CLIENTS_MAX; i++) {
        if (teams->clients[i] == 0) {
            teams->clients[i] = new_socket;
            dprintf(new_socket, "%s\r\n", HELLO);
            insert_client(&teams->client_head, new_socket);
            break;
        } else
            full_connected++;
    }
    if (full_connected == CLIENTS_MAX) {
        dprintf(new_socket,
            "Sorry, the maximum of connections authorized is reached\r\n");
        close(new_socket);
    }
}

void check_for_instructions(teams_t *teams)
{
    char buffer[1024] = {0};
    int act_fd;

    for (int i = 0; i < CLIENTS_MAX; i++) {
        act_fd = teams->clients[i];
        if (FD_ISSET(act_fd, &teams->readset)) {
            teams->act_idx = i;
            if (read(act_fd, buffer, 1024) == 0) {
                remove_client(teams->client_head, act_fd);
                close(act_fd);
                teams->clients[i] = 0;
            } else {
                bad_command(teams, act_fd);
                // manage_connection(teams, act_fd, buffer);
                send_replies(teams->client_head, teams->writeset);
            }
        }
    }
}