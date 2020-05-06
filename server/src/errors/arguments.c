/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Error handling of the arguments
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int return_and_msg(char *msg, int return_value)
{
    fprintf(stderr, "%s\n", msg);
    return (return_value);
}

int check_port(char *port_str)
{
    int port = 0;

    for (int i = 0; port_str[i]; i++) {
        if (!isdigit(port_str[i]))
            return (return_and_msg(
                "The port should only be composed of digits", -1));
    }
    port = atoi(port_str);
    if (port <= 0 || port > 65635)
        return (return_and_msg("The port should be included in [1-65535]", -1));
    return (port);
}

int error_handling(int ac, char **av)
{
    if (ac != 2)
        return (return_and_msg("The program should have only 1 argument.", -1));
    if (strlen(av[1]) == 0)
        return (return_and_msg("Arguments can't be empty", -1));
    else if (strcmp(av[1], "-help") == 0)
        return (0);
    return (check_port(av[1]));
}