/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Entry point of the commands
*/

#include <string.h>
#include "prototypes.h"
#include "structs.h"
#include "logs.h"

void help_cmd(myteams_t *teams, client_t *client, void *arg);

void manage_command(myteams_t *teams, client_t *client, char *input)
{
    if (!client)
        return;
    (void)(input);
    console_log(client, "Used a basic command", BASIC, NULL);
    if (strcmp(input, "HELP") == 0)
        help_cmd(teams, NULL, input);
    else
        bad_command(teams, client);
}