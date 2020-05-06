/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Launcher of the My Teams
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "prototypes.h"

int start_teams(myteams_t *teams)
{
    while (1) {
        reset_update_set(teams);
        if (select(teams->maxfd + 1, &teams->readset, &teams->writeset,
            NULL, NULL) == -1)
            return (return_and_msg("Error on select", 1));
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

int launch_server(int ac, char **av)
{
    myteams_t *teams;
    int errors = error_handling(ac, av);

    if (errors < 0)
        return (84);
    else if (errors == 0)
        return (display_help());
    teams = create_teams(errors);
    if (!teams || start_teams(teams) != 0)
        return (84);
    free_myteams(teams);
    return (0);
}