/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Logs header file
*/

#ifndef LOGS_H_
#define LOGS_H_

#include "structs.h"

typedef enum
{
    BASIC,
    ERROR,
    SUCCESS
} log_type;

void console_log(client_t *from, char *msg, log_type type, char *custom_color);

#endif