/*
** EPITECH PROJECT, 2019
** My teams - client
** File description:
** main.c
*/

#include <unistd.h>
#include <stdlib.h>
#include "client.h"
#include "logs.h"

int main(int ac, char **av)
{
    char *ip = NULL;
    int port = 8000;
    int sockfd = -1;
    log_t *head = NULL;

    if (ac != 3)
        return (84);
    ip = av[1];
    port = strtol(av[2], NULL, 10);
    sockfd = try_connect(ip, port);
    if (sockfd < 0)
        return (84);
    fill_commands(&head);
    manage_client(head, sockfd);
    free_logs_list(head);
    return (0);
}