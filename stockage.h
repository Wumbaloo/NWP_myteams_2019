/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <uuid/uuid.h>

#define DEFAULT_NAME_LENGTH 32
#define DEFAULT_DESCRIPTION_LENGTH 255
#define DEFAULT_BODY_LENGTH 512


typedef struct comment_s
{
    char comment_body[DEFAULT_BODY_LENGTH];
    struct comment_s *next;
} comment_t;

typedef struct thread_s
{
    char *thread_title;
    char *thread_msg;
    uuid_t thread_uuid;
    comment_t *comments;
    struct thread_s *next;
} thread_t;

typedef struct channel_s
{
    char channel_name[DEFAULT_NAME_LENGTH];
    uuid_t channel_uuid;
    char channel_desc[DEFAULT_DESCRIPTION_LENGTH];
    thread_t *threads;
    struct channel_s  *next;
} channel_t;

typedef struct team_s
{
    char team_name[DEFAULT_NAME_LENGTH];
    uuid_t team_uuid;
    char team_desc[DEFAULT_DESCRIPTION_LENGTH];
    channel_t *channels;
    struct team_s *next;
} team_t;