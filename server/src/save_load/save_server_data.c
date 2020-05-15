/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "data_storage.h"

void save_comments(comment_t *comments, char uuids[3][37], int file)
{
    comment_t *tmp = comments;
    char author_uuid[37];

    while (tmp) {
        uuid_unparse(tmp->comment_author, author_uuid);
        dprintf(file, "COMMENT \"%s\" \"%s\" \"%s\" \"%ld\" \"%s\" \"%s\"\n",
            uuids[0], uuids[1], uuids[2], tmp->timestamp,
            tmp->comment_body, author_uuid);
        tmp = tmp->next;
    }
}

void save_thread(thread_t *threads, char uuids[3][37], int file)
{
    thread_t *tmp = threads;
    char author_uuid[37];
    char thread_uuid[37];

    while (tmp) {
        uuid_unparse(tmp->thread_uuid, uuids[2]);
        uuid_unparse(tmp->thread_author, author_uuid);
        uuid_unparse(tmp->thread_uuid, thread_uuid);
        dprintf(file,
            "THREAD \"%s\" \"%s\" \"%ld\" \"%s\" \"%s\" \"%s\" \"%s\"\n",
            uuids[0], uuids[1], tmp->timestamp, tmp->thread_title,
            tmp->thread_msg, author_uuid, thread_uuid);
        save_comments(tmp->comment_head, uuids, file);
        memset(uuids[2], 0, 37);
        tmp = tmp->next;
    }
}

void save_channel(channel_t *channels, char uuids[3][37], int file)
{
    channel_t *tmp = channels;

    while (tmp) {
        uuid_unparse(tmp->channel_uuid, uuids[1]);
        dprintf(file, "CHANNEL \"%s\" \"%s\" \"%s\" \"%s\"\n", uuids[0],
            tmp->channel_name, uuids[1], tmp->channel_desc);
        save_thread(tmp->thread_head, uuids, file);
        memset(uuids[1], 0, 37);
        tmp = tmp->next;
    }
}

void save_team(myteams_t *teams, int file)
{
    team_t *tmp = teams->team_head;
    char uuids[3][37];

    while (tmp) {
        uuid_unparse(tmp->team_uuid, uuids[0]);
        dprintf(file, "TEAM \"%s\" \"%s\" \"%s\"\n", tmp->team_name, uuids[0],
            tmp->team_desc);
        save_channel(tmp->channel_head, uuids, file);
        memset(uuids[0], 0, 37);
        tmp = tmp->next;
    }
}