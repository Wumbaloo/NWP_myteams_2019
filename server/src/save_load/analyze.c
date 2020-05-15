/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Where lines in save files are analyzed
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "structs.h"
#include "prototypes.h"

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
        {"TEAM", &load_team},
        {"CHANNEL", &load_channel},
        {"THREAD", &load_thread},
        {"COMMENT", &load_comment},
        {"USER", &load_user},
        {"PRIVATE_MESSAGE", &load_team},
    };

    if (!type || !line)
        return;
    execute_save(teams, line, save_types, type);
}

int open_save_file(myteams_t *teams)
{
    FILE *fd = fopen(SAVE_FILE, "r");
    char *s = NULL;
    size_t len = 0;

    if (fd == NULL) {
        printf("FILE %s: Not found.\n", SAVE_FILE);
        return (84);
    }
    while (getline(&s, &len, fd) != -1) {
        for (size_t i = 0; i < strlen(s); i++) {
            if (s[i] == '\n')
                s[i] = '\0';
        }
        analyze_save(teams, s);
        free(s);
    }
    fclose(fd);
    return (0);
}
