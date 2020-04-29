/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <zconf.h>
#include "ftp.h"
#include "prototypes.h"

int start_ftp(ftp_t *ftp)
{
    while (1) {
        reset_update_set(ftp);
        if (select(ftp->maxfd + 1, &ftp->readset, &ftp->writeset, NULL, NULL) ==
            -1)
            return return_with_msg("Error on select", 1);
        if (FD_ISSET(ftp->server->control_socket, &ftp->readset))
            connection_received(ftp);
        check_for_instructions(ftp);
    }
    return 0;
}

int display_help(void)
{
    printf("USAGE: ./myftp port path\n"
           "\tport is the port number on which the server socket listens\n"
           "\tpath is the path to the home directory for the Anonymous user\n");
    return 0;
}

int main(int ac, char **av)
{
    ftp_t *ftp;

    if (ac == 2 && !strcmp(av[1], "-help"))
        return display_help();
    if (error_handling(ac, av))
        return 84;
    ftp = create_ftp(atoi(av[1]), av[2]);
    if (start_ftp(ftp) != 0)
        return 84;
}