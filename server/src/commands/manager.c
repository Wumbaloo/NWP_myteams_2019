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

void help_cmd(teams_t *teams, client_t *client, void *arg);

void manage_command(teams_t *teams, client_t *client, char *input)
{
    command_t *cmd = get_command(teams->command_head, input);

    if (!client)
        return;
    if (cmd)
        cmd->func(teams, client, input);
    else {
        console_log(client, "Used a bad command", ERROR, NULL);
        bad_command(teams, client);
    }
}