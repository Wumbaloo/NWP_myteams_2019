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
    char **split_array = NULL;
    int code = 0;
    log_t *current = NULL;
    char *str = NULL;
    int result = 0;

    if (!buffer)
        return (1);
    for (str = strtok(buffer, "\r\n"); str;) {
        str = clean_string(str);
        split_array = (strstr(str, "\"") ? parse_arguments(buffer, '"')
            : my_str_to_word_array(buffer, ' '));
        code = strtol(split_array[0], NULL, 10);
        current = get_log(head, code);
        free(str);
        result += (!current ? -1 : current->func(split_array));
        str = strtok(NULL, "\r\n");
        for (int i = 0; split_array[i]; i++)
            free(split_array[i]);
    }
    return (result);
}