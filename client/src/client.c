/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Client side of My FTP
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "logs.h"
#include "client.h"

char *read_from_server(int sockfd)
{
    char buffer[1024];
    char *returnBuf;
    int valread = read(sockfd, buffer, 1024);

    if (valread == -1)
        exit(84);
    returnBuf = malloc(sizeof(char) * (valread + 1));
    if (!returnBuf)
        exit(84);
    returnBuf = strcpy(returnBuf, buffer);
    returnBuf[valread] = '\0';
    return (returnBuf);
}

int try_connect(char *ip, int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in config;
    char *buffer;

    if (sockfd == -1) {
        perror("socket");
        return (-1);
    }
    config.sin_family = AF_INET;
    config.sin_port = htons(port);
    if(inet_pton(AF_INET, ip, &config.sin_addr) <= 0) { 
        write(2, "Invalid address.\n", 17);
        return (-1);
    }
    if (connect(sockfd, (struct sockaddr *) &config, sizeof(config)) < 0) {
        perror("connect");
        return (-1);
    }
    buffer = read_from_server(sockfd);
    printf("%s", buffer);
    free(buffer);
    return (sockfd);
}

int get_input(char **input)
{
    size_t len = 0;

    if (*input)
        free(*input);
    if (getline(&(*input), &len, stdin) == -1)
        return (84);
    (*input) = clean_string(*input);
    return (0);
}

void manage_client(log_t *log_head, int sockfd)
{
    char *buffer = NULL;
    char *input = NULL;
    int input_return = 0;

    while (1) {
        input_return = get_input(&input);
        if (input_return == 1)
            continue;
        else if (input_return > 0)
            break;
        dprintf(sockfd, "%s\r\n", input);
        buffer = read_from_server(sockfd);
        printf("%s", buffer);
        analyze_log(log_head, buffer);
        if (strncasecmp(input, "/logout", 7) == 0)
            break;
        free(buffer);
    }
    free(input);
}