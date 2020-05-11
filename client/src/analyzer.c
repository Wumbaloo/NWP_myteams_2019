/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Analyze answer messages
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "logs.h"

int analyze_log(log_t *head, char *buffer)
{
    char **code_str_array = NULL;
    char *end_ptr = NULL;
    int code = 0;
    log_t *current = NULL;
    char *str = NULL;
    int result = 0;

    if (!buffer)
        return (1);
    for (str = strtok(buffer, "\r\n"); str;) {
        str = clean_string(str);
        code_str_array = my_str_to_word_array(str, ' ');
        code = strtol(code_str_array[0], &end_ptr, 10);
        current = get_log(head, code);
        free(str);
        result += (!current ? -1 : current->func(code_str_array));
        str = strtok(NULL, "\r\n");
    }
    return (result);
}