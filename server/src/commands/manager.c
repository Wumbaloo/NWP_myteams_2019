/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Entry point of the commands
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"
#include "logs.h"

void manage_command(myteams_t *teams, client_t *client, char *input)
{
    command_t *cmd = NULL;
    char **cmd_tab = NULL;

    if (!client)
        return;
    cmd_tab = parse_arguments(input, '"');
    if (!cmd_tab) {
        console_log(client, "Wrong command formatting", ERROR, NULL);
        bad_command(client, NULL);
    } else if (cmd_tab[0] && cmd_tab[0][0] == '/') {
        cmd = get_command(teams->command_head, &cmd_tab[0][1]);
        if (cmd) {
            if (cmd->need_login && !client->is_connected)
                not_logged_in(client);
            else
                cmd->func(teams, client, cmd_tab);
        } else
            bad_command(client, cmd_tab[0]);
    } else
        bad_command(client, cmd_tab[0]);
    free_array(cmd_tab);
}