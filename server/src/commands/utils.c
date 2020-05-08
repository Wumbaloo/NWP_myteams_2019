/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include "structs.h"

int double_array_size(char **array)
{
    int cpt = 0;

    for (; array[cpt]; cpt++);
    return cpt;
}

bool is_banned(sub_list_t *list, uuid_t uuid)
{
    sub_list_t *copy = list;

    for (; copy; copy = copy->next)
        if (uuid_compare(copy->uuid, uuid) == 0)
            return true;
    return false;
}