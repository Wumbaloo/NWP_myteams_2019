/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Global data storage
*/

#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include <uuid/uuid.h>
#include "macros.h"

typedef struct comment_s
{
    time_t timestamp;
    char comment_body[DEFAULT_BODY_LENGTH + 1];
    uuid_t comment_author;
    struct comment_s *next;
} comment_t;

typedef struct thread_s
{
    time_t timestamp;
    char *thread_title;
    char *thread_msg;
    uuid_t thread_author;
    uuid_t thread_uuid;
    comment_t *comment_head;
    struct thread_s *next;
} thread_t;

typedef struct channel_s
{
    char channel_name[DEFAULT_NAME_LENGTH + 1];
    uuid_t channel_uuid;
    char channel_desc[DEFAULT_DESCRIPTION_LENGTH + 1];
    thread_t *thread_head;
    struct channel_s  *next;
} channel_t;

typedef struct team_s
{
    char team_name[DEFAULT_NAME_LENGTH + 1];
    uuid_t team_uuid;
    char team_desc[DEFAULT_DESCRIPTION_LENGTH + 1];
    channel_t *channel_head;
    struct team_s *next;
} team_t;

#endif