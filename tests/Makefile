NAME    = run_tests

CC		= gcc

CP  	= cp

CFLAG	=	-g3 -Wall -Wextra -luuid -lcriterion --verbose

SRC 	= 	../server/src/remove_extra_spaces.c		\
			remove_extra_spaces_tests.c				\

OBJ	 = 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAG)
	$(CP) $(NAME) ../

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)
re: fclean all

.PHONY: all clean fclean re
