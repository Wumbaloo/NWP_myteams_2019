/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** test_logs
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include "prototypes.h"
#include "structs.h"
#include "logs.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(basic_command, basic, .init=redirect_all_stdout)
{
    client_t *client = new_client(2);

    console_log(client, "Used a basic command", BASIC, NULL);
    console_log(client, "Used a command in a bad way", ERROR, NULL);
    console_log(client, "Used a command correctly", SUCCESS, NULL);
    console_log(client, "Used a command with a custom color", BASIC, "[0;35m");
    console_log(NULL, "A general basic log", BASIC, NULL);
    console_log(NULL, "A general error log", ERROR, NULL);
    console_log(NULL, "A general success log", SUCCESS, NULL);
    console_log(NULL, "A general custom color log", BASIC, "[0;35m");
    cr_assert_eq(client->fd, 2);
    free_clients_list(client);
}