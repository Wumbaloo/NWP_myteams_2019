/*
** EPITECH PROJECT, 2019
** myteams
** File description:
** init_connection.c
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "client.h"

int try_connect(char *ip, int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in config;
    char *buffer;

    if (sockfd == -1)
        return_with_perror("socket", -1);
    config.sin_family = AF_INET;
    config.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &config.sin_addr) <= 0) {
        write(2, "Invalid address.\n", 17);
        return (-1);
    }
    if (connect(sockfd, (struct sockaddr *) &config, sizeof(config)) < 0)
        return_with_perror("socket", -1);
    buffer = read_from_server(sockfd);
    printf("%s", buffer);
    free(buffer);
    return (sockfd);
}

int init_server_connection(char **av)
{
    char *ip = NULL;
    int port = 8000;

    ip = av[1];
    port = strtol(av[2], NULL, 10);
    return (try_connect(ip, port));
}

int launcher(int ac, char **av)
{
    log_t *head = NULL;
    int sockfd = 0;

    if (ac != 3)
        return (84);
    sockfd = init_server_connection(av);
    if (sockfd < 0)
        return (84);
    fill_commands(&head);
    manage_client(head, sockfd);
    free_logs_list(head);
    return (0);
}