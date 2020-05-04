/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Analyze answer messages
*/

#include <string.h>
#include <stdlib.h>
#include "client.h"
#include "logs.h"

int analyze_log(log_t *head, char *buffer)
{
    char **code_str_array = NULL;
    char *end_ptr = NULL;
    int code = 0;
    log_t *current = NULL;

    if (!buffer)
        return (1);
    code_str_array = my_str_to_word_array(buffer, ' ');
    code = strtol(code_str_array[0], &end_ptr, 10);
    current = get_log(head, code);
    if (!current)
        return (0);
    return (current->func(code_str_array));
}