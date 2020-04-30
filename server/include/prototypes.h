/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Prototypes header file
*/

#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include "structs.h"

int launch_server(int ac, char **av);

//Error handling ==> errors > error.c
int error_handling(int ac, char **av);
int return_with_msg(char *msg, int return_value);
void bad_command(teams_t *teams, int fd);

//Init the structures ==> core > initialization.c
teams_t *create_teams(int port);
client_t *new_client(int fd, char *path);

//Manage the linked list==> linked_list.c
void insert_client(client_t *first, int fd, char *path);
client_t *new_node(int fd, char *path);
void remove_client(client_t *first, int fd);
client_t *get_client(client_t *first, int fd);
void send_replies(client_t *first, fd_set wr_set);

//Core of the server requests ==> core > monitoring.c
void reset_update_set(teams_t *teams);
void connection_received(teams_t *teams);
void check_for_instructions(teams_t *teams);

//Free Things ==> free.c
void free_client(client_t *client);

//Manage the commands ==> command_handling.c
int manage_connection(teams_t *teams, int fd, char *buffer);

//Extra functions for commands ==> command_utils.c
char *get_argument(char *buffer);

//Active/Passive connection handling ==> connection_mode.cc
void set_connection_mode(teams_t *teams, char *command, int fd);

// Login handling ==> authentication.c
void try_username(teams_t *teams, int fd, char *buffer);
void try_password(teams_t *teams, int fd, char *buffer);

//Manage the working directory on server ==> working_directory.c
void change_dir_to_parent(teams_t *teams, int fd);
void print_working_directory(teams_t *teams, int fd);
void change_directory(teams_t *teams, int fd, char *buffer);

//Additional functions to working_directory ==> changedir_utils.c
int try_cat(client_t *client, char *path);
int try_from_root(char *path);
char *get_new_cat_path(char *first_part, char *second_part);
void no_arg_on_cwd(teams_t *teams, int fd);

//Utils & random commands ==> utils.c
void quit(teams_t *teams, int fd);
void print_help(teams_t *teams, int fd);
void no_operation(teams_t *teams, int fd);

//Actions on server files ==> file_action.c
void delete_file(teams_t *teams, int fd, char *buffer);

//lib
char *my_strcat(char *dest, char *src);

#endif