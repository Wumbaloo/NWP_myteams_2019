/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Free command
*/

#include <stdlib.h>
#include "structs.h"

void free_command(command_t *cmd)
{
    if (cmd->command)
        free(cmd->command);
    free(cmd);
}

void free_commands_list(command_t *head)
{
    command_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free_command(head);
        head = tmp;
    }
    if (tmp)
        free_command(tmp);
}
