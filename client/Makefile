NAME    = myteams_cli

CC		= gcc

CP  	= cp

CFLAG	=	-g3 -Wall -Wextra -luuid

SRC 	= 	src/main.c 					\
			src/send.c					\
			src/read.c					\
			src/loop_client.c			\
			src/init.c					\
			src/disconnect.c			\
			src/connect.c				\

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