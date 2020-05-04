##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Just a Makefile that compiles everything
##

SRC_DIR	=	src/

FILES	=	free.c									\
			channels/free.c							\
			channels/linked_list.c					\
			clients/free.c							\
			clients/client_getter.c					\
			clients/input.c							\
			clients/linked_list.c					\
			clients/utils.c							\
			clients/messages/free.c					\
			clients/messages/linked_list.c			\
			commands/free.c							\
			commands/linked_list.c					\
			commands/list_subscribed.c				\
			commands/listing.c						\
			commands/manager.c						\
			commands/private_message.c				\
			commands/subscription.c					\
			commands/use.c							\
			commands/users_info.c					\
			comments/free.c							\
			comments/linked_list.c					\
			core/free.c								\
			core/initialization.c					\
			core/launcher.c							\
			core/monitoring.c						\
			errors/arguments.c						\
			errors/commands.c						\
			sub_list/linked_list.c					\
			teams/free.c							\
			teams/linked_list.c						\
			threads/free.c							\
			threads/linked_list.c					\
			useful/exit.c							\
			useful/logs.c							\
			useful/my_str_to_word_array.c			\

MAIN_FILE	=	main.c

SRC			=	$(addprefix $(SRC_DIR), $(FILES))
SRC_MAIN	=	$(addprefix $(SRC_DIR), $(MAIN_FILE))

OBJ		=	$(SRC:.c=.o)
OBJ_MAIN=	$(SRC_MAIN:.c=.o)

LDFLAGS	=	-L ../lib -lmyteams -luuid
CFLAGS	=	-I include

NAME	=	../myteams_server

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	$(CC) -o $(NAME) $(OBJ) $(OBJ_MAIN) $(LDFLAGS)

debug:
	$(CC) -o $(NAME) $(SRC) $(SRC_MAIN) $(CFLAGS) -Wall -Werror -Wextra -g $(LDFLAGS)

tests_run:
	make -C tests tests_run from="$(CURDIR)" files="$(SRC)"

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(OBJ) $(OBJ_MAIN)

re: fclean all
