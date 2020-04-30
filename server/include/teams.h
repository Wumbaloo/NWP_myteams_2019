/*
** EPITECH PROJECT, 2023
** My Teams
** File description:
** Core header file
*/

#ifndef TEAMS_H_
#define TEAMS_H_

#define CLIENTS_MAX 128
#define NOT_CONNECTED "530 Please login with USER and PASS."
#define ALREADY_LOGGED "230 Already logged in."
#define CHANGE_USER "530 Can't change from guest user."
#define BAD_LOGIN "530 Login incorrect."
#define GOOD_LOGIN "230 Login successful."
#define NEED_PASSWORD "331 Please specify the password."
#define NO_USER "503 Login with USER first."
#define FAILED_CHANGEDIR "550 Failed to change directory."
#define OK_CHANGEDIR "250 Directory successfully changed."
#define OK_DELE "250 File deleted."
#define FAILED_DELE "550 Failed to delete the file."
#define BAD_CMD "500 Unknown command."
#define HELLO "220 Welcome on my_ftp's server"
#define QUIT "221 Goodbye.\r\n"
#define NOOP "200 NOOP ok."
#define USER "Anonymous"

#endif