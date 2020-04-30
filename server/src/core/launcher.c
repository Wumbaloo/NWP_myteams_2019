/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Launcher of the My Teams
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <zconf.h>
#include "teams.h"
#include "prototypes.h"

int start_teams(teams_t *teams)
{
    while (1) {
        reset_update_set(teams);
        if (select(teams->maxfd + 1, &teams->readset, &teams->writeset,
            NULL, NULL) == -1)
            return return_with_msg("Error on select", 1);
        else if (FD_ISSET(teams->server->control_socket, &teams->readset))
            connection_received(teams);
        check_for_instructions(teams);
    }
    return (0);
}

int display_help(void)
{
    printf("USAGE: ./myteams_server port\n"
           "\tport is the port number on which the server socket listens\n");
    return (0);
}

int main(int ac, char **av)
{
    teams_t *teams;

    if (ac == 2 && !strcmp(av[1], "-help"))
        return display_help();
    else if (error_handling(ac, av))
        return (84);
    teams = create_teams(atoi(av[1]), av[2]);
    if (!teams || start_teams(teams) != 0)
        return (84);
}