##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC     	=	src/server/main.c					\
					src/server/error.c					\
					src/server/free.c					\
					src/server/struct_initialization.c	\
					src/server/linked_list.c			\
					src/server/command_handling.c		\
					src/server/authentication.c			\
					src/server/connection_mode.c		\
					src/server/utils.c					\
					src/server/working_directory.c		\
					src/server/my_strcat.c				\
					src/server/changedir_utils.c		\
					src/server/command_utils.c			\
					src/server/file_action.c			\
					src/server/server_monitoring.c		\

OBJ     	=		$(SRC:.c=.o)

NAME    	=	myftp

CFLAGS 	=	-I include/ -W -Wall -Wextra


all: $(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
