/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#include <fcntl.h>
#include <stdio.h>
#include "macros.h"
#include "structs.h"

void load(myteams_t *teams)
{
    FILE *file = fopen(SAVE_FILE, "r");
    char *buffer = NULL;
    size_t len = 0;
    ssize_t line_size = 0;

    if (!file) {
        dprintf(2, "Failed to open the file\n");
        return;
    }
    line_size = getline(&buffer, &len, file);
    while (line_size >= 0) {
        
        line_size = getline(&buffer, &len, file);
    }
}