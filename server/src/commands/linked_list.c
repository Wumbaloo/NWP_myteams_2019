/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Commands linked list
*/

#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "prototypes.h"

void insert_command(command_t **head, command_t *node)
{
    command_t *tmp = (*head);

    if (!(*head)) {
        *head = node;
        return;
    }
    for (; tmp->next; tmp = tmp->next);
    tmp->next = node;
}

void remove_command(command_t *head, command_t *node)
{
    command_t *tmp = head;

    if (!head || !node)
        return;
    while (tmp->next) {
        if (tmp->next == node && tmp->next->next
            && tmp->next->next == node->next) {
            tmp->next = node->next;
            free_command(node);
            break;
        }
    }
}

command_t *get_command(command_t *head, char *cmd)
{
    command_t *tmp = head;

    if (!head)
        return (NULL);
    while (tmp) {
        if (strcmp(tmp->command, cmd) == 0)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}
