/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Clients storage header file (clients and private messages)
*/

#ifndef CLIENTS_STORAGE_H_
#define CLIENTS_STORAGE_H_

#include <uuid/uuid.h>
#include <stdbool.h>
#include "macros.h"

typedef enum
{
    TEAM,
    CHANNEL,
    THREAD,
    COMMENT
} use_depth;

typedef struct message_s
{
    uuid_t sender;
    uuid_t receiver;
    char body[DEFAULT_BODY_LENGTH];
    struct message_s *next;
} message_t;

typedef struct user_s
{
    int fd;
    bool is_connected;
    char *reply;
    char user_name[DEFAULT_NAME_LENGTH];
    uuid_t user_uuid;
    use_depth depth;
    uuid_t *group_tab;
    uuid_t *channel_tab;
    uuid_t *thread_tab;
    message_t *message_head;
    struct user_s *next;
    struct command_s *command_head;
} client_t;

#endif