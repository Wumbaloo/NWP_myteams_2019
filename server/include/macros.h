/*
** EPITECH PROJECT, 2023
** NWP_myteams_2019
** File description:
** Created by Anthony ANICOTTE,
*/

#define DEFAULT_NAME_LENGTH 32
#define DEFAULT_DESCRIPTION_LENGTH 255
#define DEFAULT_BODY_LENGTH 512

#define CLIENTS_MAX 128

#define RESPONSE_SIZE 2048

#define CONNECTED "042"
#define DISCONNECTED "084"
#define TEAM_CREATED "110"
#define SUCCESS_CREATED_TEAM "120"
#define LIST_TEAM "130"
#define INFO_TEAM "140"
#define JOIN_TEAM "142"
#define LEAVE_TEAM "184"
#define CHANNEL_CREATED "210"
#define SUCCESS_CREATED_CHANNEL "220"
#define LIST_CHANNEL "230"
#define INFO_CHANNEL "240"
#define THREAD_CREATED "310"
#define SUCCESS_CREATED_THREAD "320"
#define LIST_THREAD "330"
#define INFO_THREAD "340"
#define REPLY_POSTED "410"
#define SUCCESS_REPLY_POSTED "420"
#define LIST_REPLY "430"
#define PM_RECEIVED "510"
#define LIST_PM "530"
#define UNKNOWN_TEAM "605"
#define UNKNOWN_CHANNEL "615"
#define UNKNOWN_THREAD "625"
#define UNKNOWN_USER "635"
#define UNAUTHORIZED "645"
#define ALREADY_EXISTS "655"
#define INFO_USER "740"




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
#define HELLO "220 Welcome on our teams server"
#define QUIT "221 Goodbye.\r\n"
#define NOOP "200 NOOP ok."
#define USER "Anonymous"