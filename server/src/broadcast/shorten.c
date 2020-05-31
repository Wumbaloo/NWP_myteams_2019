/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <uuid/uuid.h>
#include <stdlib.h>

void optimize(char *thread_uuid, char *user_uuid, uuid_t client, uuid_t thread)
{
    uuid_unparse(client, user_uuid);
    uuid_unparse(thread, thread_uuid);
}

void multi_free(char *str_one, char *str_two)
{
    free(str_one);
    free(str_two);
}