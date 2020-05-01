/*
** EPITECH PROJECT, 2018
** my_str_to_word_array.c
** File description:
** my_str_to_word_array.c
*/

#include <unistd.h>
#include <stdlib.h>

char *my_strncpy_2(char *dest, char *src, int to, int nb)
{
    int i = 0;
    int j = nb - to;

    if (nb == 1) {
        dest[0] = '\0';
        return (dest);
    }
    for (int z = 0; z < j; z++)
        dest[i++] = src[to++];
    dest[j - 1] = '\0';
    return (dest);
}

char *last_malloc(char *av, int from, int to)
{
    char *str = NULL;

    str = malloc(sizeof(char) * ((from - to) + 1));
    if (str == NULL)
        exit(84);
    str = my_strncpy_2(str, av, to, from + 1);
    str[(from - to)] = '\0';
    return (str);
}

char **first_malloc(char **array, int nb_word)
{
    array = malloc(sizeof(char *) * (nb_word + 1));
    if (array == NULL)
        exit(84);
    array[nb_word] = NULL;
    return (array);
}

char **concat_my_array(char *av, int nb_word, char separate, int to)
{
    char **array = NULL;
    int y = 0;
    int from = 0;

    if ((array = first_malloc(array, nb_word)) == NULL)
        exit(84);
    for (int index = 0; av[index] != '\0'; index++) {
        from++;
        if (av[index] == separate && av[index + 1] != separate) {
            array[y] = malloc(sizeof(char) * ((from - to) + 1));
            if (array[y] == NULL)
                exit(84);
            array[y] = my_strncpy_2(array[y], av, to, from);
            y++;
            to = from;
        }
    }
    array[y] = last_malloc(av, from, to);
    array[y] == NULL ? exit(84) : NULL;
    return (array);
}

char **my_str_to_word_array(char *av, char separate)
{
    char **array = NULL;
    int nb_words = 1;

    for (int index = 0; av[index] != '\0'; index++) {
        if (av[index] == separate && av[index + 1] != separate)
            nb_words++;
    }
    array = concat_my_array(av, nb_words, separate, 0);
    if (array == NULL)
        exit(84);
    return (array);
}