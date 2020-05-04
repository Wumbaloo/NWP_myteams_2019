/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Free logs
*/

#include <stdlib.h>
#include "logs.h"

void free_log(log_t *log)
{
    free(log);
}

void free_logs_list(log_t *head)
{
    log_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free_log(head);
        head = tmp;
    }
    if (tmp)
        free_log(tmp);
}
