/*
** EPITECH PROJECT, 2019
** My teams - client
** File description:
** client.h
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include "logs.h"

void fill_commands(log_t **head);
void analyze_log(log_t *head, char *buffer);
void manage_client(log_t *log_head, int sockfd);
int try_connect(char *ip, int port);
char *clean_string(char *str);
char **my_str_to_word_array(char *av, char separate);

#endif