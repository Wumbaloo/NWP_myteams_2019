/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Where structures are initialized,
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "teams.h"
#include "prototypes.h"

client_t *new_client(int fd, char *path)
{
    client_t *client = malloc(sizeof(client_t));
    char buf[PATH_MAX];

    if (!client) {
        perror("malloc");
        exit(84);
    }
    client->fd = fd;
    realpath(path, buf);
    client->folder_path = strdup(buf);
    if (!client->folder_path) {
        perror("malloc");
        exit(84);
    }
    client->username = UNDEFINED;
    client->password = UNDEFINED;
    client->is_connected = false;
    client->reply = NULL;
    client->current_directory = opendir(path);
    client->mode = NONE;
    return client;
}

server_t *create_server(int control_port)
{
    server_t *server = malloc(sizeof(server_t));
    socklen_t server_length;
    int reuse = 1;

    if (!server) {
        perror("malloc");
        exit(84);
    }
    server->control_socket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server->control_socket, SOL_SOCKET, SO_REUSEPORT, &reuse,
        sizeof(int));
    if (server->control_socket < 0) {
        perror("socket");
        exit(84);
    }
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(control_port);
    server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_length = sizeof(server->addr);
    if (bind(server->control_socket, (struct sockaddr *)&server->addr,
        server_length) == -1)
        exit(84);
    if (listen(server->control_socket, CLIENTS_MAX) == -1)
        exit(84);
    return (server);
}

teams_t *create_teams(int port)
{
    teams_t *teams = malloc(sizeof(teams_t));

    teams->server = create_server(port);
    teams->clients = malloc(sizeof(int) * CLIENTS_MAX);
    for (int i = 0; i < CLIENTS_MAX; i++)
        teams->clients[i] = 0;
    teams->maxfd = 0;
    teams->client_head = new_node(-42, "/");
    return (teams);
}