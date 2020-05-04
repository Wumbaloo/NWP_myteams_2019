/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Logs linked list
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "logs.h"

void insert_log(log_t **head, log_t *node)
{
    log_t *tmp = (*head);

    if (!(*head)) {
        *head = node;
        return;
    }
    for (; tmp->next; tmp = tmp->next);
    tmp->next = node;
}

log_t *create_log(log_t **head, int code, int (*func)(char **))
{
    log_t *new = malloc(sizeof(log_t));

    if (!new) {
        perror("malloc");
        exit(84);
    }
    new->code = code;
    new->func = func;
    new->next = NULL;
    insert_log(head, new);
    return (new);
}

void remove_log(log_t *head, log_t *node)
{
    log_t *tmp = head;

    if (!head || !node)
        return;
    while (tmp->next) {
        if (tmp->next == node && tmp->next->next
            && tmp->next->next == node->next) {
            free_log(node);
            break;
        }
        tmp->next = node->next;
    }
}

log_t *get_log(log_t *head, int code)
{
    log_t *tmp = head;

    if (!head)
        return (NULL);
    while (tmp) {
        if (tmp->code == code)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}
