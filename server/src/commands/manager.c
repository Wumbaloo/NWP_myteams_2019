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

void help_cmd(myteams_t *teams, client_t *client, void *arg);

char *get_quote_content(char *str)
{
    int idx = 0;
    int size = strlen(str);
    char *new_str = malloc(sizeof(char) * (size - 1));

    if (!new_str)
        exit(84);
    for (int i = 1; i < strlen(str) - 1; i++)
        new_str[idx++] = str[i];
    new_str[idx] = '\0';
    return (new_str);
}

int quote_parser(char *input)
{
    if (input[0] != '"' || input[strlen(input) - 1] != '"')
        return (-1);
    return (0);
}

void execute_command(myteams_t *teams, client_t *client, char **cmd_tab,
                        command_t *cmd)
{
    if (cmd_tab[1]) {
        if (quote_parser(cmd_tab[1]) == -1) {
            console_log(client, "Used a bad command", ERROR, NULL);
            bad_command(teams, client);
            return;
        } else
            cmd->func(teams, client, get_quote_content(cmd_tab[1]));
    } else
        cmd->func(teams, client, &cmd_tab[0]);
}

void manage_command(myteams_t *teams, client_t *client, char *input)
{
    command_t *cmd = NULL;
    char **cmd_tab = NULL;

    if (!client)
        return;
    cmd_tab = my_str_to_word_array(input, ' ');
    if (cmd_tab[0] && cmd_tab[0][0] == '/') {
        cmd = get_command(teams->command_head, &cmd_tab[0][1]);
        if (cmd) {
            execute_command(teams, client, cmd_tab, cmd);
            return;
        }
    }
    console_log(client, "Used a bad command", ERROR, NULL);
    bad_command(teams, client);
    free_array(cmd_tab);
}