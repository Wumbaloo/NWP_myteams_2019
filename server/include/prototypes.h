/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Prototypes header file
*/

#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "structs.h"

//Useful functions ==> useful
void perror_exit(char *err, int exit_code);

//Error handling ==> errors > error.c
int error_handling(int ac, char **av);
int return_with_msg(char *msg, int return_value);
void bad_command(teams_t *teams, int fd);

//Core prototypes in ==> core
teams_t *create_teams(int port);
client_t *new_client(int fd);
int launch_server(int ac, char **av);
//    Server requests ==> core > monitoring.c
void reset_update_set(teams_t *teams);
void connection_received(teams_t *teams);
void check_for_instructions(teams_t *teams);

//Manage the linked list ==> clients > linked_list.c
client_t *new_node(int fd);
client_t *get_client(client_t *first, int fd);
void insert_client(client_t **first, int fd);
void remove_client(client_t *first, int fd);
void send_replies(client_t *first, fd_set wr_set);

//Manage commands in ==> commands
int manage_connection(teams_t *teams, int fd, char *buffer);

//Free Things
void free_client(client_t *client);
void free_list(client_t *head);
void free_teams(teams_t *teams);

#endif