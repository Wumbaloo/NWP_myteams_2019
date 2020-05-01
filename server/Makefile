##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Just a Makefile that compiles everything
##

SRC_DIR	=	src/

FILES	=	clients/free.c						\
			clients/input.c						\
			clients/linked_list.c				\
			clients/utils.c						\
			clients/messages/linked_list.c		\
			commands/free.c						\
			commands/linked_list.c				\
			commands/listing.c					\
			commands/manager.c					\
			core/free.c							\
			core/initialization.c				\
			core/launcher.c						\
			core/monitoring.c					\
			errors/arguments.c					\
			errors/commands.c					\
			useful/exit.c						\
			useful/logs.c						\

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
