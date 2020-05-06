##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Receive "files" (a list of C files) and "from" (directory of call)
##

TEST_FILES	=	test_client_linked_list.c	\
				test_commands_linked_list.c	\
				test_logs.c					\

NAME = unit_tests

all: $(NAME)

$(NAME): tests_run

tests_run:
ifdef files
ifdef from
	$(CC) -o $(NAME) $(addprefix $(subst ${space} ,\ ,$(from)/), $(files)) $(TEST_FILES) -I $(subst ${space} ,\ ,$(from)/include) --coverage -lcriterion -L ../../lib -lmyteams -luuid
	./$(NAME)
else
	@echo 'No from directory for unit tests.'
endif
else
	@echo 'No files found for unit tests.'
endif

clean:
	rm -f $(NAME)

fclean: clean
	rm -f *.gcda *.gch *.gcno *.o

re: fclean all
