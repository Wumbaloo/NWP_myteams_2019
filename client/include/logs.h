/*
** EPITECH PROJECT, 2019
** My Teams
** File description:
** Logs header file
*/

#ifndef LOGS_H_
#define LOGS_H_

typedef struct log_s {
    int code;
    void (*func)(char **);
    struct log_s *next;
} log_t;

log_t *create_log(log_t **head, int code, void (*func)(char **));
log_t *get_log(log_t *head, int code);
void free_log(log_t *log);
void free_logs_list(log_t *head);
void insert_log(log_t **head, log_t *node);

#endif