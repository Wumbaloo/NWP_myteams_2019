/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Prototypes header file
*/

#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include "structs.h"

//Error handling ==> error.c
int error_handling(int ac, char **av);
int return_with_msg(char *msg, int return_value);
void bad_command(ftp_t *ftp, int fd);

//Init the structures ==> struct_initialization.c
ftp_t *create_ftp(int port, char *dir_path);
client_t *new_client(int fd, char *path);

//Manage the linked list==> linked_list.c
void insert_client(element *first, int fd, char *path);
element *new_node(int fd, char *path);
void remove_client(element *first, int fd);
client_t *get_client(element *first, int fd);
void send_replies(element *first, fd_set wr_set);

//Core of the server requests ==> server_monitoring.c
void reset_update_set(ftp_t *ftp);
void connection_received(ftp_t *ftp);
void check_for_instructions(ftp_t *ftp);

//Free Things ==> free.c
void free_client(client_t *client);

//Manage the commands ==> command_handling.c
int manage_connection(ftp_t *ftp, int fd, char *buffer);

//Extra functions for commands ==> command_utils.c
char *get_argument(char *buffer);

//Active/Passive connection handling ==> connection_mode.cc
void set_connection_mode(ftp_t *ftp, char *command, int fd);

// Login handling ==> authentication.c
void try_username(ftp_t *ftp, int fd, char *buffer);
void try_password(ftp_t *ftp, int fd, char *buffer);

//Manage the working directory on server ==> working_directory.c
void change_dir_to_parent(ftp_t *ftp, int fd);
void print_working_directory(ftp_t *ftp, int fd);
void change_directory(ftp_t *ftp, int fd, char *buffer);

//Additional functions to working_directory ==> changedir_utils.c
int try_cat(client_t *client, char *path);
int try_from_root(char *path);
char *get_new_cat_path(char *first_part, char *second_part);
void no_arg_on_cwd(ftp_t *ftp, int fd);

//Utils & random commands ==> utils.c
void quit(ftp_t *ftp, int fd);
void print_help(ftp_t *ftp, int fd);
void no_operation(ftp_t *ftp, int fd);

//Actions on server files ==> file_action.c
void delete_file(ftp_t *ftp, int fd, char *buffer);

//lib
char *my_strcat(char *dest, char *src);

#endif