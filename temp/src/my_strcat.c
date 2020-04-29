/*
** EPITECH PROJECT, 2018
** strcat
** File description:
** task2
*/

#include <stdlib.h>
#include <string.h>

char *my_strcat(char *dest, char *src)
{
    int cpt = 0;
    int j = strlen(dest);
    char *str = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));

    for (int i = 0; dest[i] != '\0'; i++)
        str[i] = dest[i];
    while (src[cpt] != '\0') {
        str[j] = src[cpt];
        cpt++;
        j++;
    }
    str[j] = '\0';
    return (str);
}