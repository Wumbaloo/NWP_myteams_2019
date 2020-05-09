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
    UNDEFINED,
    TEAM,
    CHANNEL,
    THREAD
} use_depth;

typedef struct message_s
{
    time_t timestamp;
    uuid_t sender;
    uuid_t receiver;
    char body[DEFAULT_BODY_LENGTH];
    struct message_s *next;
} message_t;

typedef struct sub_list_s
{
    uuid_t uuid;
    struct sub_list_s *next;
} sub_list_t;

typedef struct replies_s
{
    char *reply;
    struct replies_s *next;
} replies_t;

typedef struct user_s
{
    int fd;
    bool is_connected;
    replies_t *replies;
    char user_name[DEFAULT_NAME_LENGTH];
    uuid_t user_uuid;
    use_depth depth;
    uuid_t team_chosen;
    uuid_t channel_chosen;
    uuid_t thread_chosen;
    sub_list_t *team_tab;
    sub_list_t *channel_tab;
    sub_list_t *thread_tab;
    message_t *message_head;
    struct user_s *next;
} client_t;

#endif