/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <uuid/uuid.h>
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
    char user_name[DEFAULT_NAME_LENGTH];
    uuid_t user_uuid;
    use_depth depth;
    uuid_t *group_tab;
    uuid_t *channel_tab;
    uuid_t *thread_tab;
    uuid_t *comment_tab;
    message_t *message_head;
    struct user_s *user_head;
} user_t;