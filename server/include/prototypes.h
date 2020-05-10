/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Prototypes header file
*/

#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "logs.h"
#include "structs.h"

//Clients prototypes ==> clients
char *read_from_client(int fd);

//Commands prototypes ==> commands
int bad_cmd_parameters(client_t *client, char *cmd);
void bad_command(client_t *client, char *cmd);
void not_logged_in(client_t *client);

void create_all_commands(command_t **head);
void insert_command(command_t **head, command_t *node);
void remove_command(command_t *head, command_t *node);
void manage_command(myteams_t *teams, client_t *client, char *input);
void free_command(command_t *cmd);
void free_commands_list(command_t *head);
command_t *get_command(command_t *head, char *cmd);
command_t *create_command(char *txt, int login,
                            int (*ptr)(myteams_t *, client_t *, char **));
int login_cmd(myteams_t *teams, client_t *client, char **arg);
int logout_cmd(myteams_t *teams, client_t *client, char **arg);

int specific_user_cmd(myteams_t *teams, client_t *client, char **arg);
int specific_message_cmd(myteams_t *teams, client_t *client, char **arg);
int subscribe_cmd(myteams_t *teams, client_t *client, char **arg);
int unsubscribe_cmd(myteams_t *teams, client_t *client, char **arg);
int info_cmd(myteams_t *teams, client_t *client, char **input);
int create_cmd(myteams_t *teams, client_t *client, char **input);
int info_cmd(myteams_t *teams, client_t *client, char **input);
int list_cmd(myteams_t *teams, client_t *client, char **input);
int use_cmd(myteams_t *teams, client_t *client, char **input);
bool already_subscribed(sub_list_t *head, uuid_t team);
void subscribe_to_subchannels(sub_list_t *channel_list, team_t *team);

//Command utils
int double_array_size(char **array);
bool is_banned(sub_list_t *list, uuid_t uuid);

//Parser functions ==> commandes/parser
char **parse_arguments(char *input, char separator);
int remove_quotes_args(char **cmd_tab);
int char_array_length(char **array);
int count_words(char *input, char separator);
int is_banned_char(char c);

//Useful functions ==> useful
void perror_exit(char *err, int exit_code);
void console_log(client_t *from, char *msg, log_type type, char *custom_color);
void free_array(char **arr);
char **my_str_to_word_array(char *av, char separate);
int uuid_tab_size(uuid_t *array);
char *format_response(int nbr,  ...);
int reply_unauthorized(client_t *client);
int reply_resource_already_exists(client_t *client);
int reply_unknown_user(client_t *client, char *user_uuid);
int reply_unknown_thread(client_t *client, char *thread_uuid);
int reply_unknown_channel(client_t *client, char *channel_uuid);
int reply_unknown_team(client_t *client, char *team_uuid);

//Error handling ==> errors > error.c
int error_handling(int ac, char **av);
int return_and_msg(char *msg, int return_value);

//Core prototypes in ==> core
myteams_t *create_teams(int port);
client_t *new_client(int fd);
int launch_server(int ac, char **av);

//Server requests ==> core > monitoring.c
void reset_update_set(myteams_t *teams);
void connection_received(myteams_t *teams);
void check_for_instructions(myteams_t *teams);

//Manage commands in ==> commands
int manage_connection(myteams_t *teams, int fd, char *buffer);

//Clients linked-list
int nbr_clients(client_t *head);
client_t *get_client_by_fd(client_t *head, int fd);
client_t *get_client_by_uuid(client_t *head, uuid_t uuid);
client_t *get_client_by_username(client_t *head, char *username);
void duplicate_client(client_t *src, client_t *dest);
int nbr_duplicates(client_t *head, uuid_t uuid);
void insert_client(client_t **first, int fd);
void remove_client(client_t *first, int fd);
void send_replies(myteams_t *teams, client_t *first, fd_set wr_set);

//Clients->Messages linked-list
void insert_message(message_t **first, uuid_t from, uuid_t to,
    char body[DEFAULT_BODY_LENGTH]);

//Subscription linked-list
void insert_in_sub_list(sub_list_t **first, uuid_t uuid);
void remove_in_sub_list(sub_list_t *first, uuid_t uuid);

//Teams linked-list
void insert_team(team_t **first, char name[DEFAULT_NAME_LENGTH],
    char desc[DEFAULT_DESCRIPTION_LENGTH]);
team_t *get_team_by_uuid(team_t *head, uuid_t uuid);
team_t *get_team_by_name(team_t *head, char *name);

//Channels linked-list
void insert_channel(channel_t **first, char name[DEFAULT_NAME_LENGTH],
    char desc[DEFAULT_DESCRIPTION_LENGTH]);
channel_t *get_channel_by_uuid(channel_t *head, uuid_t uuid);
channel_t *get_channel_by_name(channel_t *head, char *name);

//Thread linked-list
void insert_thread(thread_t **first, char *title, char *content, uuid_t author);
thread_t *new_thread(char *title, char *content, uuid_t author);
thread_t *get_thread_by_uuid(thread_t *head, uuid_t uuid);
thread_t *get_thread_by_title(thread_t *head, char *name);

//Comments linked-list
void insert_comment(comment_t **first, char body[DEFAULT_BODY_LENGTH],
    uuid_t author);
comment_t *new_comment(char body[DEFAULT_BODY_LENGTH], uuid_t author);

//Replies linked_list
void insert_reply(replies_t **first, char *reply);
void send_next_reply(myteams_t *team, int fd);
void remove_reply(replies_t **replies_head);

//Broadcast
void broadcast_team_created(myteams_t *teams, client_t *client,  team_t *team);
void broadcast_channel_created(myteams_t *teams, client_t *client, channel_t *channel);
void broadcast_thread_created(myteams_t *teams, client_t *client, thread_t *thread);
void broadcast_comment_created(myteams_t *teams, client_t *client, comment_t *comment);
void broadcast_unsubscription(client_t *client, char *team_uuid);
void broadcast_subscription(client_t *client, char *team_uuid);

//Free Things
void free_myteams(myteams_t *myteams);
void free_client(client_t *client);
void free_clients_list(client_t *head);
void free_teams(myteams_t *teams);
void free_messages_list(message_t *head);
void free_comments_list(comment_t *head);
void free_threads_list(thread_t *head);
void free_channels_list(channel_t *head);
void free_teams_list(team_t *head);

#endif