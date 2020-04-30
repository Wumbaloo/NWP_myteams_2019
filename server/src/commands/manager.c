/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Entry point of the commands
*/

#include <string.h>
#include "prototypes.h"
#include "structs.h"

void help_cmd(teams_t *teams, client_t *client, void *arg);

void manage_command(teams_t *teams, int fd, char *input)
{
    (void)(input);
    if (strcmp(input, "HELP") == 0)
        help_cmd(teams, NULL, input);
    else
        bad_command(teams, fd);
}