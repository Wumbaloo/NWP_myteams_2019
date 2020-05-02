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

void login_cmd(myteams_t *teams, client_t *client, void *arg)
{
    char uuid[36];
    client_t *temp = get_client_by_username(teams->client_head, arg);

    if (temp != NULL)
        duplicate_client(temp, client);
    else {
        uuid_generate(client->user_uuid);
        memcpy(client->user_name, arg, DEFAULT_NAME_LENGTH);
        client->is_connected = true;
    }
//    client->reply = strdup("LOGIN command");
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_logged_in(uuid);
//    console_log(client, "LOGIN", BASIC, NULL);
}

void logout_cmd(myteams_t *teams, client_t *client, void *arg)
{
    (void)(arg);
    console_log(client, "LOGOUT", BASIC, NULL);
    if (FD_ISSET(client->fd, &teams->writeset))
        dprintf(client->fd, "221 Good bye!\n");
    close(client->fd);
    teams->clients[teams->act_idx] = 0;
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