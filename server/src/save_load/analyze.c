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

int count_parameters(char *input, char separator)
{
    int len = strlen(input);
    int nb_args = 0;

    for (int index = 0; (index + 1) < len; index++) {
        if (input[index] == separator && input[index + 1] != separator) {
            for (; index < len && input[index + 1] != separator; index++);
            index++;
            nb_args++;
        }
    }
    return (nb_args);
}

int is_space_char(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int fill_parameters(char **array, char *input, char separator, int from)
{
    int y = 0;
    int copy = 0;

    for (int i = from; input[i] != '\0'; i++) {
        if (input[i] == separator && input[i + 1] != separator && !copy) {
            for (; input[i] && (is_space_char(input[i]) ||
                (input[i] == separator && input[i + 1] == separator)); i++);
            from = i + 1;
            copy = 1;
        } else if (input[i] == separator && copy) {
            array[y] = malloc(sizeof(char) * ((i - from) + 1));
            if (array[y] == NULL)
                return (1);
            array[y] = strncpy(array[y], input + from, (i - from));
            array[y++][i - from] = '\0';
            copy = 0;
            for (; input[i] && (is_space_char(input[i]) ||
                (input[i] == separator && input[i + 1] == separator)); i++);
        }
    }
    return (0);
}

char **get_parameters(char *line, char separator)
{
    char **array = NULL;
    int nb_args = 0;
    int error = count_occurences_letter(line, separator) % 2;

    nb_args = ((error != 0) ? 2 : count_parameters(line, separator));
    array = malloc(sizeof(char *) * (nb_args + 1));
    if (!array)
        exit(84);
    array[nb_args] = NULL;
    if (error != 0)
        return (NULL);
    fill_parameters(array, line, separator, 0);
    return (array);
}

char *get_saved_type(char *line)
{
    char *type = NULL;

    if (!line)
        return (NULL);
    printf("Line is |%s|\n", line);
    type = strtok(line, " ");
    if (!type)
        return (NULL);
    return (type);
}

void analyze_save(myteams_t *teams, char *line)
{
    char **split = NULL;
    char *type = get_saved_type(line);

    if (!type || !line)
        return;
    printf("Type is %s\n", type);
    split = get_parameters(line + strlen(type) + 1, '\"');
    for (int i = 0; split[i]; i++)
        printf("%s\n", split[i]);
}

int main(void)
{
    char *line = "TEAM \"Salut\" \"c23a75a8-d9b9-40f2-9492-ead6e036bec2\" \"ok\"";
    
    analyze_save(NULL, line);
}