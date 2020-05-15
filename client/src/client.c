/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Client side of My FTP
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include "client.h"

char *read_from_server(int sockfd)
{
    char buffer[1024];
    char *returnBuf = NULL;
    int valread = read(sockfd, buffer, 1024);

    if (valread == 0)
        return (NULL);
    if (valread == -1)
        exit(84);
    buffer[valread] = '\0';
    returnBuf = strdup(buffer);
    if (!returnBuf)
        exit(return_with_perror("malloc", 84));
    return (returnBuf);
}

void reset_update_set(int socket, fd_set *readset, fd_set *writeset)
{
    FD_ZERO(readset);
    FD_ZERO(writeset);
    FD_SET(socket, readset);
    FD_SET(0, readset);
}

int is_server_readable(char *buffer, int sockfd, fd_set *readset,
    log_t *log_head)
{
    int result = 0;

    if (FD_ISSET(sockfd, readset)) {
        buffer = read_from_server(sockfd);
        if (!buffer)
            return (1);
        result = analyze_log(log_head, buffer);
        if (result < 0)
            printf("%s", buffer);
    }
    return (result);
}

int is_server_writable(char *input, int sockfd, fd_set *readset)
{
    int input_return = 0;

    if (FD_ISSET(0, readset)) {
        input_return = get_input(&input);
        if (input_return == 84)
            return (2);
        else if (input_return > 0)
            return (1);
        dprintf(sockfd, "%s\r\n", input);
    }
    return (0);
}

void manage_client(log_t *log_head, int sockfd)
{
    char *buffer = NULL;
    char *input = NULL;
    int input_return = 0;
    fd_set readset;
    fd_set writeset;

    while (1) {
        reset_update_set(sockfd, &readset, &writeset);
        if (select(sockfd + 1, &readset, &writeset,
            NULL, NULL) == -1)
            return;
        else if (is_server_readable(buffer, sockfd, &readset, log_head) == 1)
            break;
        input_return = is_server_writable(input, sockfd, &readset);
        if (input_return == 2)
            continue;
        else if (input_return == 1)
            break;
    }
    free(input);
}