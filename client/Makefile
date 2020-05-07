##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Just a Makefile that compiles everything
##

SRC_DIR	=	src/

FILES	=	logs/fill.c						\
			logs/free.c						\
			logs/linked_list.c				\
			useful/array.c					\
			useful/clean_str.c				\
			useful/my_str_to_word_array.c	\
			useful/get_input.c				\
			errors/error.c					\
			analyzer.c						\
			init_connection.c				\
			client.c						\

MAIN_FILE	=	main.c

SRC			=	$(addprefix $(SRC_DIR), $(FILES))
SRC_MAIN	=	$(addprefix $(SRC_DIR), $(MAIN_FILE))

OBJ		=	$(SRC:.c=.o)
OBJ_MAIN=	$(SRC_MAIN:.c=.o)

LDFLAGS	=	-L ../libs -lmyteams -luuid
CFLAGS	+=	-I include

NAME	=	../myteams_cli

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	$(CC) -o $(NAME) $(OBJ) $(OBJ_MAIN) $(LDFLAGS)

debug:
	$(CC) -o $(NAME) $(SRC) $(SRC_MAIN) $(CFLAGS) $(LDFLAGS) -Wall -Werror -Wextra -g

tests_run:
	make -C tests tests_run from="$(CURDIR)" files="$(SRC)"

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(OBJ) $(OBJ_MAIN)

re: fclean all
