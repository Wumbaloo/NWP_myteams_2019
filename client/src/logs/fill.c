/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Fill logs functions and head
*/

#include <stdio.h>
#include "logging_client.h"
#include "client.h"
#include "logs.h"

void fill_errors(log_t **head)
{
    create_log(head, 601, &bad_cmd_trigger);
    create_log(head, 602, &bad_params_trigger);
    create_log(head, 605, &unknown_team_trigger);
    create_log(head, 615, &unknown_channel_trigger);
    create_log(head, 625, &unknown_thread_trigger);
    create_log(head, 635, &unknown_user_trigger);
    create_log(head, 642, &already_logged_in_trigger);
    create_log(head, 645, &unauthorized_trigger);
    create_log(head, 655, &already_exists_trigger);
}

void fill_next_commands(log_t **head)
{
    create_log(head, 310, &create_thread_event_trigger);
    create_log(head, 320, &create_thread_specific_trigger);
    create_log(head, 330, &list_threads);
    create_log(head, 340, &info_thread);
    create_log(head, 410, &create_reply_event_trigger);
    create_log(head, 420, &create_reply_specific_trigger);
    create_log(head, 430, &list_replies);
    create_log(head, 510, &private_message_trigger);
    create_log(head, 530, &list_private_messages_trigger);
    create_log(head, 730, &users_list_trigger);
    create_log(head, 740, &specific_user_trigger);
}

void fill_commands(log_t **head)
{
    create_log(head, 42, &login_trigger);
    create_log(head, 84, &logout_trigger);
    create_log(head, 110, &create_team_event_trigger);
    create_log(head, 120, &create_team_specific_trigger);
    create_log(head, 130, &list_teams);
    create_log(head, 140, &info_team);
    create_log(head, 142, &user_join_team_trigger);
    create_log(head, 184, &unsubscribe_trigger);
    create_log(head, 210, &create_channel_event_trigger);
    create_log(head, 220, &create_channel_specific_trigger);
    create_log(head, 230, &list_channels);
    create_log(head, 240, &info_channel);
    fill_next_commands(head);
    fill_errors(head);
}