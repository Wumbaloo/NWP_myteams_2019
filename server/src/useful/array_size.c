/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <uuid/uuid.h>

int uuid_tab_size(uuid_t *array)
{
    int cpt = 0;

    for (; array[cpt]; cpt++);
    return cpt;
}