/*
** EPITECH PROJECT, 2019
** My teams - client
** File description:
** client.h
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include "logs.h"

// Simple triggers
int bad_cmd_trigger(char **array);
int bad_params_trigger(char **array);
int not_logged_in_trigger(char **array);
int unauthorized_trigger(char **array);
int already_logged_in_trigger(char **array);
int users_list_trigger(char **array);
int specific_user_trigger(char **array);
int unknown_user_trigger(char **array);
int private_message_trigger(char **array);
int list_private_messages_trigger(char **array);
int create_team_specific_trigger(char **array);
int create_team_trigger(char **array);
int user_join_team_trigger(char **array);

// Events
int create_channel_event_trigger(char **array);

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
char *concat_array(char **array, int begin);
char *get_arg_array(char **array, int index);
char **parse_arguments(char *input, char separator);
int count_occurences_letter(char *input, char separator);

// Parser utils
int char_array_length(char **array);
int count_words(char *input, char separator);
int is_parser_char(char c);

#endif