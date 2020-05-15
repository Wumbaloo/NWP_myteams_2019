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
#include "data_storage.h"
#include "clients_storage.h"

typedef struct server_s
{
    struct sockaddr_in addr;
    int control_socket;
    int control_port;
} server_t;

typedef struct myteams_s
{
    server_t *server;
    int maxfd;
    int act_idx;
    int *clients;
    fd_set readset;
    fd_set writeset;
    client_t *client_head;
    team_t *team_head;
    struct command_s *command_head;
} myteams_t;

typedef struct command_s
{
    int need_login;
    char *command;
    int (*func)(myteams_t *, client_t *, char **);
    struct command_s *next;
} command_t;

typedef struct save_type_s
{
    char *type;
    void (*func)(myteams_t *, char **);
} save_type_t;

#endif