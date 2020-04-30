/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <uuid/uuid.h>
#include "macros.h"

typedef struct comment_s
{
    char comment_body[DEFAULT_BODY_LENGTH];
    uuid_t comment_author;
    struct comment_s *next;
} comment_t;

typedef struct thread_s
{
    char *thread_title;
    char *thread_msg;
    uuid_t thread_author;
    uuid_t thread_uuid;
    comment_t *comment_head;
    struct thread_s *next;
} thread_t;

typedef struct channel_s
{
    char channel_name[DEFAULT_NAME_LENGTH];
    uuid_t channel_uuid;
    char channel_desc[DEFAULT_DESCRIPTION_LENGTH];
    thread_t *thread_head;
    struct channel_s  *next;
} channel_t;

typedef struct team_s
{
    char team_name[DEFAULT_NAME_LENGTH];
    uuid_t team_uuid;
    char team_desc[DEFAULT_DESCRIPTION_LENGTH];
    channel_t *channel_head;
    struct team_s *next;
} team_t;