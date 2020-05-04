/*
** EPITECH PROJECT, 2019
** my_teams
** File description:
** error.c
*/

#include <stdio.h>

int return_with_perror(char *msg, int value)
{
    perror("msg");
    return (value);
}