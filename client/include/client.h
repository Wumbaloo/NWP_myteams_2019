/*
** EPITECH PROJECT, 2019
** My teams - client
** File description:
** client.h
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include "logs.h"

int bad_cmd_trigger(char **array);
int bad_params_trigger(char **array);
int not_logged_in_trigger(char **array);
int already_logged_in_trigger(char **array);
int analyze_log(log_t *head, char *buffer);
int get_array_length(char **array);
void fill_commands(log_t **head);
void manage_client(log_t *log_head, int sockfd);
char *read_from_server(int sockfd);
int return_with_perror(char *msg, int value);
int get_input(char **input);
char *clean_string(char *str);
int launcher(int ac, char **av);
char **my_str_to_word_array(char *av, char separate);

#endif