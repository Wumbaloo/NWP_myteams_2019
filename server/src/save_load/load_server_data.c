/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

void load_comment(myteams_t *teams, char **array)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    uuid_t uuid;
    comment_t *comment;

    uuid_parse(array[1], uuid);
    team = get_team_by_uuid(teams->team_head, uuid);
    uuid_parse(array[2], uuid);
    channel = get_channel_by_uuid(team->channel_head, uuid);
    uuid_parse(array[3], uuid);
    thread = get_thread_by_uuid(channel->thread_head, uuid);
    uuid_parse(array[6], uuid);
    insert_comment(&thread->comment_head, array[5], uuid);
    comment = get_comment(thread->comment_head, uuid, array[5],
        strtol(array[4], NULL, 10));
    comment->timestamp = strtol(array[4], NULL, 10);
}

void load_thread(myteams_t *teams, char **array)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    uuid_t uuid;

    uuid_parse(array[1], uuid);
    team = get_team_by_uuid(teams->team_head, uuid);
    uuid_parse(array[2], uuid);
    channel = get_channel_by_uuid(team->channel_head, uuid);
    uuid_parse(array[6], uuid);
    insert_thread(&channel->thread_head, array[4], array[5], uuid);
    uuid_parse(array[7], uuid);
    thread = get_thread_by_title(channel->thread_head, array[4]);
    uuid_copy(thread->thread_uuid, uuid);
    thread->timestamp = strtol(array[3], NULL, 10);
}

void load_channel(myteams_t *teams, char **array)
{
    team_t *team;
    channel_t *channel;
    uuid_t uuid;

    team = get_team_by_uuid(teams->team_head, uuid);
    insert_channel(&team->channel_head, array[2], array[4]);
    channel = get_channel_by_name(team->channel_head, array[2]);
    uuid_parse(array[1], uuid);
    uuid_copy(channel->channel_uuid, uuid);
}

void load_team(myteams_t *teams, char **array)
{
    team_t *team;
    uuid_t uuid;

    insert_team(&teams->team_head, array[1], array[3]);
    team = get_team_by_name(teams->team_head, array[1]);
    uuid_parse(array[2], uuid);
    uuid_copy(team->team_uuid, uuid);
}