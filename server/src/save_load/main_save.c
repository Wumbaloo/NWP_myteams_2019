/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include "structs.h"
#include "prototypes.h"

void save(myteams_t *teams)
{
    int file = open(SAVE_FILE, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    client_t *client = teams->client_head;

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
    while (client) {
        logout_cmd(teams, client, NULL);
        client = client->next;
    }
}