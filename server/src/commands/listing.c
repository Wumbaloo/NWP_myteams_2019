/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Commands listing
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "logging_server.h"
#include "prototypes.h"
#include "structs.h"
#include "logs.h"

command_t *create_command(char *txt, int login,
                            void (*ptr)(myteams_t *, client_t *, void *))
{
    command_t *cmd = malloc(sizeof(command_t));
    int len = strlen(txt);

    if (cmd == NULL)
        perror_exit("malloc", 84);
    cmd->command = malloc(sizeof(char) * (len + 1));
    if (cmd->command == NULL)
        perror_exit("malloc", 84);
    strcpy(cmd->command, txt);
    cmd->command[len] = '\0';
    cmd->func = ptr;
    cmd->need_login = login;
    cmd->next = NULL;
    return (cmd);
}

void help_cmd(myteams_t *teams, client_t *client, void *arg)
{
    (void)(teams);
    (void)(client);
    (void)(arg);
//    console_log(client, "HELP", BASIC, NULL);
    client->reply = strdup("HELP command");
}

void create_all_commands(command_t **head)
{
    command_t *help = create_command("HELP", 0, help_cmd);
    command_t *login = create_command("LOGIN", 0, login_cmd);
    command_t *logout = create_command("LOGOUT", 0, logout_cmd);

    insert_command(head, help);
    insert_command(head, login);
    insert_command(head, logout);
}