/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ftp.h"
#include "prototypes.h"

client_t *new_client(int fd, char *path)
{
    client_t *client = malloc(sizeof(client_t));
    char buf[PATH_MAX];

    client->fd = fd;
    realpath(path, buf);
    client->folder_path = strdup(buf);
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

    server->control_socket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server->control_socket, SOL_SOCKET, SO_REUSEPORT, &reuse,
        sizeof(int));
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(control_port);
    server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_length = sizeof(server->addr);
    bind(server->control_socket, (struct sockaddr *)&server->addr,
        server_length);
    listen(server->control_socket, CLIENTS_MAX);
    return server;
}

ftp_t *create_ftp(int port, char *dir_path)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));

    ftp->server = create_server(port);
    ftp->clients = malloc(sizeof(int) * CLIENTS_MAX);
    for (int i = 0; i < CLIENTS_MAX; i++)
        ftp->clients[i] = 0;
    ftp->maxfd = 0;
    ftp->default_path = strdup(dir_path);
    ftp->firstnode = new_node(-42, dir_path);
    return ftp;
}