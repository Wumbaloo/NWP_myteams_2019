/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** test_client_linked_list
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"

Test(insert_client, insert_when_empty)
{
    client_t *head = NULL;

    insert_client(&head, 2);
    cr_assert_eq(head->fd, 2);
    free_clients_list(head);
}

Test(insert_client, basic_insert)
{
    client_t *head = new_client(2);

    if (!head)
        exit(84);
    insert_client(&head, 2);
    cr_assert_eq(head->next->fd, 2);
    free_clients_list(head);
}

Test(delete_node, delete_when_empty)
{
    client_t *head = NULL;

    remove_client(head, 1);
    cr_assert_eq(head, NULL);
    free_clients_list(head);
}

Test(delete_node, basic_delete)
{
    client_t *head = new_client(1);

    if (!head)
        exit(84);
    insert_client(&head, 2);
    insert_client(&head, 5);
    remove_client(head, 2);
    cr_assert_eq(head->next->fd, 5);
    free_clients_list(head);
}

Test(delete_node, delete_inexistant)
{
    client_t *head = new_client(1);
    client_t *node = new_client(2);

    if (!head)
        exit(84);
    if (!node)
        exit(84);
    node->next = NULL;
    head->next = NULL;
    remove_client(head, 2);
    cr_assert_eq(head->next, NULL);
    free_clients_list(head);
    free_clients_list(node);
}

Test(get_client_fd, empty_fd_getter)
{
    client_t *head = NULL;

    cr_assert_eq(get_client_by_fd(head, 1), NULL);
}

Test(get_client_fd, normal_fd_getter)
{
    client_t *head = new_client(1);
    client_t *node = new_client(2);

    if (!head || !node)
        exit(84);
    node->next = NULL;
    head->next = node;
    cr_assert_eq(get_client_by_fd(head, 2), node);
    free_clients_list(head);
}

Test(get_client_fd, getter_fd_inexistant)
{
    client_t *head = new_client(1);
    client_t *node = new_client(2);

    if (!head || !node)
        exit(84);
    node->next = NULL;
    head->next = NULL;

    cr_assert_eq(get_client_by_fd(head, 2), NULL);
    free_clients_list(head);
    free_clients_list(node);
}
