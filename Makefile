##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Just a Makefile that compiles everything
##

NAME	=	myteams

all: $(NAME)

$(NAME):
	make -C server
	make -C client

client:
	make -C client

server:
	make -C server

debug:
	make debug -C server
	make debug -C client

tests_run:
	make tests_run -C client
	make tests_run -C server

clean:
	make clean -C server
	make clean -C client

fclean: clean
	make fclean -C server
	make fclean -C client

re: fclean all
