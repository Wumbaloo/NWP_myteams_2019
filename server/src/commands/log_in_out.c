/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "prototypes.h"
#include "logging_server.h"

void broadcast_login(client_t *head, char *uuid, char *user_name)
{
    client_t *copy = head;
    char *reply = format_response(3, CONNECTED, uuid, user_name);

    for (; copy; copy = copy->next) {
        if (copy->is_connected)
            insert_reply(&copy->replies, reply);
    }
    free(reply);
}

void broadcast_logout(client_t *head, char *uuid, char *user_name)
{
    client_t *copy = head;
    char *reply = format_response(3, DISCONNECTED, uuid, user_name);

    for (; copy; copy = copy->next)
        if (copy->is_connected)
            insert_reply(&copy->replies, reply);
    free(reply);
}

int not_the_first_connection(myteams_t *teams, client_t *client, char *username)
{
    client_t *temp = get_client_by_username(teams->client_head, username);
    int temp_fd;
    char uuid[36];

    if (temp->is_connected == false) {
        temp_fd = client->fd;
        remove_client(teams->client_head, client->fd);
        temp->is_connected = true;
        temp->fd = temp_fd;
    } else
        duplicate_client(temp, client);
    uuid_unparse(temp->user_uuid, uuid);
    server_event_user_logged_in(uuid);
    return (0);
}

int login_cmd(myteams_t *teams, client_t *client, char **input)
{
    char uuid[36];

    if (double_array_size(input) != 2 ||
        (input[1] && strlen(input[1]) > DEFAULT_NAME_LENGTH))
        return (bad_cmd_parameters(client, "login"));
    else if (client->is_connected == true)
        return (1);
    if (get_client_by_username(teams->client_head, input[1]))
        return (not_the_first_connection(teams, client, input[1]));
    uuid_generate(client->user_uuid);
    for (int i = 0; input[1][i] && i < DEFAULT_NAME_LENGTH; i++)
        client->user_name[i] = input[1][i];
    client->is_connected = true;
    uuid_unparse(client->user_uuid, uuid);
    server_event_user_created(uuid, client->user_name);
    server_event_user_logged_in(uuid);
    broadcast_login(teams->client_head, uuid, client->user_name);
    return (0);
}

void ok_logout_and_close(myteams_t *teams, client_t *client, char *uuid)
{
    char *reply;

    if (FD_ISSET(client->fd, &teams->writeset)) {
        reply = format_response(3, DISCONNECTED, uuid, client->user_name);
        dprintf(client->fd, "%s\r\n", reply);
        free(reply);
        close(client->fd);
        teams->clients[teams->act_idx] = 0;
    }
}

int logout_cmd(myteams_t *teams, client_t *client,
    __attribute__((unused)) char **input)
{
    char uuid[36];
    char name[DEFAULT_NAME_LENGTH + 1];

    if (client->is_connected == false)
        return (reply_unauthorized(client));
    uuid_unparse(client->user_uuid, uuid);
    ok_logout_and_close(teams, client, uuid);
    memset(name, '\0', DEFAULT_NAME_LENGTH + 1);
    for (int i = 0; client->user_name[i] && i < DEFAULT_NAME_LENGTH; i++)
        name[i] = client->user_name[i];
    if (nbr_duplicates(teams->client_head, client->user_uuid) > 1)
        remove_client(teams->client_head, client->fd);
    else {
        client->is_connected = false;
        uuid_clear(client->team_chosen);
        uuid_clear(client->channel_chosen);
        uuid_clear(client->thread_chosen);
        client->depth = UNDEFINED;
        client->fd = -1;
    }
    server_event_user_logged_out(uuid);
    broadcast_logout(teams->client_head, uuid, name);
    return (0);
}