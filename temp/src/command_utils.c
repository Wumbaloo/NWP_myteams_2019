/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** Created by Anthony ANICOTTE,
*/

#include <string.h>

char *get_argument(char *buffer)
{
    char *token = NULL;

    token = strtok(buffer, " ");
    token = strtok(NULL, " ");
    token[strlen(token) - 2] = '\0';
    return token;
}