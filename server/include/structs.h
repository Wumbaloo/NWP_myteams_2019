/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Structures header file
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include <netinet/in.h>
#include <stdbool.h>
#include <dirent.h>

typedef enum
{
    UNDEFINED,
    FALSE,
    TRUE
} auth_state;

typedef enum
{
    NONE,
    PASSIVE,
    ACTIVE
} connection_mode;

typedef struct server_s
{
    struct sockaddr_in addr;
    int control_socket;
    int data_socket;
    int control_port;
    int data_port;
} server_t;

typedef struct client_s
{
    int fd;
    auth_state username;
    auth_state password;
    bool is_connected;
    char *reply;
    connection_mode mode;
    struct client_s *next;
} client_t;

typedef struct teams_s
{
    server_t *server;
    int maxfd;
    int act_idx;
    int *clients;
    fd_set readset;
    fd_set writeset;
    client_t *client_head;
} teams_t;

#endif