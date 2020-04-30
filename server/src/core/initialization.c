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

client_t *new_client(int fd)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client)
        perror_exit("malloc", 84);
    client->fd = fd;
    client->username = UNDEFINED;
    client->password = UNDEFINED;
    client->is_connected = false;
    client->reply = NULL;
    client->mode = NONE;
    return (client);
}

void setup_server_config(server_t *server, int control_port)
{
    int reuse = 1;

    if (setsockopt(server->control_socket, SOL_SOCKET, SO_REUSEPORT, &reuse,
        sizeof(int)) < 0)
        perror_exit("setsockopt", 84);
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(control_port);
    server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

server_t *create_server(int control_port)
{
    server_t *server = malloc(sizeof(server_t));
    socklen_t server_length;

    if (!server)
        perror_exit("malloc", 84);
    server->control_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->control_socket < 0)
        perror_exit("malloc", 84);
    setup_server_config(server, control_port);
    server_length = sizeof(server->addr);
    if (bind(server->control_socket, (struct sockaddr *)&server->addr,
        server_length) == -1)
        perror_exit("bind", 84);
    if (listen(server->control_socket, CLIENTS_MAX) == -1)
        perror_exit("listen", 84);
    return (server);
}

teams_t *create_teams(int port)
{
    teams_t *teams = malloc(sizeof(teams_t));

    if (!teams)
        perror_exit("malloc", 84);
    teams->server = create_server(port);
    teams->clients = malloc(sizeof(int) * CLIENTS_MAX);
    if (!teams->clients)
        perror_exit("malloc", 84);
    for (int i = 0; i < CLIENTS_MAX; i++)
        teams->clients[i] = 0;
    teams->maxfd = 0;
    teams->client_head = NULL;
    create_all_commands(&teams->command_head);
    return (teams);
}