/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** test_reply_linked_list
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"
replies_t *new_reply(char *reply);

Test(insert_reply, insert_reply_when_empty)
{
    replies_t *head = NULL;

    insert_reply(&head, "toto");
    cr_assert_str_eq(head->reply, "toto");
    remove_reply(&head);
}

Test(insert_reply, basic_insert_reply)
{
    replies_t *head = new_reply("toto");

    if (!head)
        exit(84);
    insert_reply(&head, "tata");
    cr_assert_str_eq(head->next->reply, "tata");
    remove_reply(&head->next);
    remove_reply(&head);
}

Test(delete_node, delete_reply_when_empty)
{
    replies_t *head = NULL;

    remove_reply(&head);
    cr_assert_eq(head, NULL);
}

Test(delete_node, basic_reply_delete)
{
    replies_t *head = new_reply("toto");

    if (!head)
        exit(84);
    insert_reply(&head, "tata");
    insert_reply(&head, "tutu");
    remove_reply(&head);
    cr_assert_str_eq(head->next->reply, "tutu");
    remove_reply(&head);
}

Test(delete_node, delete_reply_inexistant)
{
    replies_t *head = new_reply("toto");
    replies_t *node = new_reply("tata");

    if (!head)
        exit(84);
    else if (!node)
        exit(84);
    node->next = NULL;
    head->next = NULL;
    remove_reply(&head);
    cr_assert_eq(head, NULL);
    remove_reply(&node);
}

Test(delete_node, delete_reply_advanced)
{
    replies_t *head = NULL;

    insert_reply(&head, "toto");
    insert_reply(&head, "tata");
    insert_reply(&head, "tutu");
    remove_reply(&head);
    cr_assert_str_eq(head->next->reply, "tutu");
    remove_reply(&head);
    cr_assert_str_eq(head->reply, "tutu");
    remove_reply(&head);
}

