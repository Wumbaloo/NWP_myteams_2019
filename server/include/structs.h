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

typedef struct
{
    struct sockaddr_in addr;
    int control_socket;
    int data_socket;
    int control_port;
    int data_port;
} server_t;

typedef struct
{
    int fd;
    auth_state username;
    auth_state password;
    bool is_connected;
    char *reply;
    char *folder_path;
    DIR *current_directory;
    connection_mode mode;
} client_t;

typedef struct element element;

struct element
{
    client_t *client;
    element *next;
};

typedef struct
{
    server_t *server;
    char *default_path;
    int maxfd;
    int act_idx;
    int *clients;
    fd_set readset;
    fd_set writeset;
    element *firstnode;
} teams_t;

#endif