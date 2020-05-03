/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Clientside logs tests
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "logs.h"

Test(insert_log, insert_when_empty)
{
    log_t *head = NULL;
    log_t *node = malloc(sizeof(log_t));

    if (!node)
        exit(84);
    node->code = 2;
    node->next = NULL;
    insert_log(&head, node);
    cr_assert_eq(head->code, 2);
    free_logs_list(head);
}

Test(insert_log, basic_insert)
{
    log_t *head = malloc(sizeof(log_t));
    log_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(log_t));
    if (!node)
        exit(84);
    head->code = 1;
    head->next = NULL;
    node->code = 2;
    node->next = NULL;
    insert_log(&head, node);
    cr_assert_eq(head->next->code, 2);
    free_logs_list(head);
}

Test(remove_log, delete_when_empty)
{
    log_t *head = NULL;

    remove_log(head, head);
    cr_assert_eq(head, NULL);
    free_logs_list(head);
}

Test(remove_log, basic_delete)
{
    log_t *head = malloc(sizeof(log_t));
    log_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(log_t));
    if (!node)
        exit(84);
    head->code = 1;
    node->code = 2;
    node->next = NULL;
    head->next = node;
    remove_log(head, node);
    cr_assert_eq(head->next, NULL);
    free_logs_list(head);
}

Test(remove_log, advanced_delete)
{
    log_t *head = malloc(sizeof(log_t));
    log_t *node = malloc(sizeof(log_t));
    log_t *node1 = malloc(sizeof(log_t));

    if (!head || !node || !node1)
        exit(84);
    head->code = 1;
    node->code = 2;
    node1->code = 3;
    head->next = node;
    node->next = node1;
    node1->next = NULL;
    remove_log(head, node);
    cr_assert_eq(head->next->code, 3);
    free_logs_list(head);
}

Test(remove_log, delete_inexistant)
{
    log_t *head = malloc(sizeof(log_t));
    log_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(log_t));
    if (!node)
        exit(84);
    head->code = 1;
    node->code = 2;
    node->next = NULL;
    head->next = NULL;
    remove_log(head, node);
    cr_assert_eq(head->next, NULL);
    free_logs_list(head);
    free_logs_list(node);
}

Test(get_log, empty_getter)
{
    log_t *head = NULL;

    cr_assert_eq(get_log(head, 1), NULL);
}

Test(get_log, normal_getter)
{
    log_t *head = malloc(sizeof(log_t));
    log_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(log_t));
    if (!node)
        exit(84);
    head->code = 1;
    node->code = 2;
    node->next = NULL;
    head->next = node;

    cr_assert_eq(get_log(head, 2), node);
    free_logs_list(head);
}

Test(get_log, getter_inexistant)
{
    log_t *head = malloc(sizeof(log_t));
    log_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(log_t));
    if (!node)
        exit(84);
    head->code = 1;
    node->code = 2;
    node->next = NULL;
    head->next = NULL;

    cr_assert_eq(get_log(head, 2), NULL);
    free_logs_list(head);
    free_logs_list(node);
}
