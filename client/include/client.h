/*
** EPITECH PROJECT, 2019
** My teams - client
** File description:
** client.h
*/

#ifndef CLIENT_H_
#define CLIENT_H_

void manage_client(int sockfd);
int try_connect(char *ip, int port);
char *clean_string(char *str);

#endif