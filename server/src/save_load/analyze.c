/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Where lines in save files are analyzed
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "prototypes.h"

int team_trigger(myteams_t *teams, char **array)
{
    printf("I'm in the TEAM trigger with :\n");
    for (int i = 0; array[i]; i++)
        printf("%s\n", array[i]);
}

void execute_save(myteams_t *teams, char *line, save_type_t *save_types,
    char *type)
{
    char **split = get_parameters(line + strlen(type) + 1, '\"');

    if (!split)
        return;
    for (int i = 0; i < 7; i++) {
        if (strcmp(save_types[i].type, type) == 0) {
            save_types[i].func(teams, split);
            break;
        }
    }
    for (int i = 0; split[i]; i++)
        free(split[i]);
    free(split);
}

void analyze_save(myteams_t *teams, char *line)
{
    char *type = get_saved_type(line);
    save_type_t save_types[7] = {
        {"TEAM", &team_trigger},
        {"CHANNEL", &team_trigger},
        {"THREAD", &team_trigger},
        {"COMMENT", &team_trigger},
        {"USER", &team_trigger},
        {"PRIVATE_MESSAGE", &team_trigger},
    };

    if (!type || !line)
        return;
    execute_save(teams, line, save_types, type);
}