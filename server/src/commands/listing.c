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
                            int (*ptr)(myteams_t *, client_t *, char **))
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

int help_cmd(myteams_t *teams, client_t *client, char **arg)
{
    char *temp_help = strdup("Send a command by using /{commandName}\nAvailable commands are:\n-/help\n/login");

    (void)(teams);
    (void)(arg);
    insert_reply(&client->replies, temp_help);
    free(temp_help);
    return 0;
}

void create_all_commands(command_t **head)
{
   command_t *help = create_command("HELP", 0, help_cmd);
   command_t *login = create_command("LOGIN", 0, login_cmd);
   command_t *logout = create_command("LOGOUT", 0, logout_cmd);
   command_t *users = create_command("USERS", 1, users_cmd);
   command_t *user = create_command("USER", 1, specific_user_cmd);
   command_t *send = create_command("SEND", 1, send_cmd);
   command_t *messages = create_command("MESSAGES", 1, specific_message_cmd);
//    command_t *subscribe = create_command("SUBSCRIBE", 0, subscribe_cmd);
//    command_t *subscribed = create_command("SUBSCRIBED", 0, subscribed_cmd);
//    command_t *unsubscribe = create_command("SUBSCRIBE", 0, unsubscribe_cmd);
//    command_t *use = create_command("USE", 0, use_cmd);
   command_t *create = create_command("CREATE", 1, create_cmd);
//    command_t *list = create_command("LIST", 0, list_cmd);
//    command_t *info = create_command("INFO", 0, info_cmd);

   insert_command(head, help);
   insert_command(head, login);
   insert_command(head, logout);
   insert_command(head, users);
   insert_command(head, user);
   insert_command(head, send);
   insert_command(head, messages);
   insert_command(head, create);
}