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

//Clients prototypes ==> clients
char *read_from_client(int fd);

//Commands prototypes ==> commands
void bad_command(myteams_t *teams, client_t *client);
void create_all_commands(command_t **head);
void insert_command(command_t **head, command_t *node);
void remove_command(command_t *head, command_t *node);
void manage_command(myteams_t *teams, client_t *client, char *input);
void free_command(command_t *cmd);
void free_commands_list(command_t *head);
command_t *get_command(command_t *head, char *cmd);
command_t *create_command(char *txt, int login,
                            void (*ptr)(myteams_t *, client_t *, void *));

//Messages
message_t *new_message(uuid_t from, uuid_t to, char body[DEFAULT_BODY_LENGTH]);
void insert_message(message_t **first, uuid_t from, uuid_t to, char body[DEFAULT_BODY_LENGTH]);

//Useful functions ==> useful
void perror_exit(char *err, int exit_code);

//Error handling ==> errors > error.c
int error_handling(int ac, char **av);
int return_with_msg(char *msg, int return_value);

//Core prototypes in ==> core
myteams_t *create_teams(int port);
client_t *new_client(int fd);
int launch_server(int ac, char **av);
//    Server requests ==> core > monitoring.c
void reset_update_set(myteams_t *teams);
void connection_received(myteams_t *teams);
void check_for_instructions(myteams_t *teams);

//Manage the linked list ==> clients > linked_list.c
client_t *new_node(int fd);
client_t *get_client(client_t *first, int fd);
void insert_client(client_t **first, int fd);
void remove_client(client_t *first, int fd);
void send_replies(client_t *first, fd_set wr_set);

//Manage commands in ==> commands
int manage_connection(myteams_t *teams, int fd, char *buffer);

//Free Things
void free_client(client_t *client);
void free_clients_list(client_t *head);
void free_teams(myteams_t *teams);

#endif