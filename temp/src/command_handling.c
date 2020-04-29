/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <string.h>
#include "ftp.h"
#include "prototypes.h"

int manage_connection(ftp_t *ftp, int fd, char *buffer)
{
    if (!strcasecmp(buffer, "CDUP\r\n"))
        change_dir_to_parent(ftp, fd);
    else if (!strcasecmp(buffer, "PWD\r\n"))
        print_working_directory(ftp, fd);
    else if (!strcasecmp(buffer, "HELP\r\n"))
        print_help(ftp, fd);
    else if (!strcasecmp(buffer, "QUIT\r\n"))
        quit(ftp, fd);
    else if (!strcasecmp(buffer, "NOOP\r\n"))
        no_operation(ftp, fd);
    else if (!strncasecmp(buffer, "USER ", 5))
        try_username(ftp, fd, buffer);
    else if (!strncasecmp(buffer, "PASS ", 5))
        try_password(ftp, fd, buffer);
    else if (!strcasecmp(buffer, "CWD\r\n") ||
    !strncasecmp(buffer, "CWD \r\n", 6))
        no_arg_on_cwd(ftp, fd);
    else if (!strncasecmp(buffer, "CWD ", 4))
        change_directory(ftp, fd, buffer);
    else if (!strncasecmp(buffer, "DELE ", 5))
        delete_file(ftp, fd, buffer);
    else if (!strcmp(buffer, "\r\n"))
        return 0;
    else
        bad_command(ftp, fd);
    return 0;
}