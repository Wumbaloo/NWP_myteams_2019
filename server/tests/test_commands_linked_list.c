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

Test(insert_command, insert_null_when_empty)
{
    command_t *head = NULL;

    insert_command(&head, head);
    cr_assert_eq(head, NULL);
    free_commands_list(head);
}

Test(insert_command, insert_when_empty)
{
    command_t *head = NULL;
    command_t *node = create_command("toto", 1, NULL);

    if (!node)
        exit(84);
    insert_command(&head, node);
    cr_assert_str_eq(head->command, "toto");
    free_commands_list(head);
}

Test(insert_command, basic_insert)
{
    command_t *head = create_command("tortue", 1, NULL);
    command_t *node = create_command("toto", 0, NULL);

    if (!head || !node)
        exit(84);
    insert_command(&head, node);
    cr_assert_str_eq(head->next->command, "toto");
    free_commands_list(head);
}

Test(remove_command, delete_when_empty)
{
    command_t *head = NULL;

    remove_command(head, NULL);
    cr_assert_eq(head, NULL);
    free_commands_list(head);
}

Test(remove_command, basic_delete)
{
    command_t *head = create_command("tortue", 1, NULL);
    command_t *toto = create_command("toto", 0, NULL);
    command_t *tata = create_command("tata", 0, NULL);

    if (!head)
        exit(84);
    insert_command(&head, toto);
    insert_command(&head, tata);
    remove_command(head, toto);
    cr_assert_str_eq(head->next->command, "tata");
    free_commands_list(head);
}

Test(remove_command, delete_inexistant)
{
    command_t *head = create_command("tortue", 1, NULL);
    command_t *node = create_command("toto", 0, NULL);

    if (!head)
        exit(84);
    if (!node)
        exit(84);
    node->next = NULL;
    head->next = NULL;
    remove_command(head, node);
    cr_assert_eq(head->next, NULL);
    free_commands_list(head);
    free_commands_list(node);
}

Test(get_command, empty_getter)
{
    command_t *head = NULL;

    cr_assert_eq(get_command(head, "tortue"), NULL);
}

Test(get_command, normal_getter)
{
    command_t *head = create_command("tortue", 1, NULL);
    command_t *node = create_command("toto", 0, NULL);

    if (!head || !node)
        exit(84);
    node->next = NULL;
    head->next = node;
    cr_assert_eq(get_command(head, "toto"), node);
    free_commands_list(head);
}

Test(get_command, getter_inexistant)
{
    command_t *head = create_command("tortue", 1, NULL);
    command_t *node = create_command("toto", 0, NULL);

    if (!head || !node)
        exit(84);
    node->next = NULL;
    head->next = NULL;

    cr_assert_eq(get_command(head, "toto"), NULL);
    free_commands_list(head);
    free_commands_list(node);
}
