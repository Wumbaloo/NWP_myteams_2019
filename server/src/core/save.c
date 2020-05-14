/*
** EPITECH PROJECT, 2019
** my_teams
** File description:
** save.c
*/

#include <stdio.h>
#include "prototypes.h"
#include "structs.h"

void save_comments(command_t *comments, char *team_uuid, char *channel_uuid, char *thread_uuid)
{
    comment_t *tmp = comments;
    char author_uuid[36];

    while (tmp) {
        uuid_unparse(tmp->comment_author, author_uuid);
        printf("%s\n", tmp->comment_body);
        // sauvegarder_commentaires_info();
        tmp = tmp->next;
    }
}

void save_thread(thread_t *threads, char *team_uuid, char *channel_uuid)
{
    thread_t *tmp = threads;
    char thread_uuid[36];

    while (tmp) {
        uuid_unparse(tmp->thread_uuid, thread_uuid);
        printf("%s\n", tmp->thread_title);
        // sauvegarder_thread_info();
        save_comments(tmp->comment_head, team_uuid, channel_uuid, thread_uui);
        tmp = tmp->next;
    }
}

void save_channel(channel_t *channels, replies_t *uuids)
{
    channel_t *tmp = channels;
    char channel_uuid[36];

    while (tmp) {
        // uuid_unparse(tmp->channel_uuid, channel_uuid);
        printf("%s\n", tmp->channel_name);
        save_thread(tmp->thread_head, team_uuid, channel_uuid);
        // sauvegarder_channel_info();
        tmp = tmp->next;
    }
}

void save(myteams_t *teams)
{
    team_t *tmp = teams->team_head;
    char uuid[36];
    replies_t *uuids = NULL;

    while (tmp) {
        uuid_unparse(tmp->team_uuid, uuid);
        // insert_reply(&uuids, uuid);
        printf("%s\n", tmp->team_name);
        save_channel(tmp->channel_head, uuids);
        // sauvegarder_team_info();
        tmp = tmp->next;
    }
}

int shutdown_cmd(myteams_t *teams, client_t *client, char **input)
{
    (void)(input);
    printf("here\n");
    // save(teams, client);
    return (1);
}

