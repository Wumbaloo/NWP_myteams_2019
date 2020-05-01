/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Log system to keep a trace
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "logs.h"

char *get_color_by_type(log_type type)
{
    switch (type) {
        case BASIC:
            return ("[0m");
        case ERROR:
            return ("[1;31m");
        case SUCCESS:
            return ("[0;32m");
    }
}

char *get_color(log_type type, char *base_color)
{
    if (!base_color)
        return (get_color_by_type(type));
    return (base_color);
}

void setup_msg_with_client(char *new_msg, char *msg, char *color, int fd)
{
    size_t len = 0;

    len = snprintf(NULL, 0, "\033[0;33mClient %d\033[0m: \033%s%s.",
        fd, color, msg);
    new_msg = malloc(sizeof(char) * (len + 1));
    if (!new_msg)
        return;
    sprintf(new_msg, "\033[0;33mClient %d\033[0m: \033%s%s.",
        fd, color, msg);
}

void console_log(client_t *from, char *msg, log_type type, char *base_color)
{
    char *new_msg = NULL;
    char *color = get_color(type, base_color);
    size_t len = 0;

    if (!msg)
        return;
    if (from)
        setup_msg_with_client(new_msg, msg, color, from->fd);
    else {
        len = snprintf(NULL, 0, "\033%s%s.", color, msg);
        new_msg = malloc(sizeof(char) * (len + 1));
        if (!new_msg)
            return;
        sprintf(new_msg, "\033%s%s.", color, msg);
    }
    printf("\033[0;36m[LOG]\033[0m %s\r\n", new_msg);
    free(new_msg);
}