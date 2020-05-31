/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>
#include "structs.h"
#include "prototypes.h"

void logout_all_clients(myteams_t *teams, client_t *client)
{
    char *specific = NULL;
    char uuid[36];
    char name[DEFAULT_NAME_LENGTH + 1];

    while (client) {
        uuid_unparse(client->user_uuid, uuid);
        memset(name, '\0', DEFAULT_NAME_LENGTH + 1);
        for (int i = 0; client->user_name[i] && i < DEFAULT_NAME_LENGTH; i++)
            name[i] = client->user_name[i];
        specific = format_response(4, DISCONNECTED, uuid, name, "1");
        dprintf(client->fd, "%s\r\n", specific);
        logout_cmd(teams, client, NULL);
        client = client->next;
    }
}

void save(myteams_t *teams)
{
    int file = open(SAVE_FILE, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (file == -1) {
        printf("Error opening the file\n");
        return;
    }
    printf("Starting writing in the file...\n");
    save_team(teams, file);
    save_users(teams, file);
    printf("Writing finished.\n");
    close(file);
    printf("File closed.\n");
    logout_all_clients(teams, teams->client_head);
}