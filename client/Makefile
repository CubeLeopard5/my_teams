NAME    = myteams_cli

CC		= gcc

CP  	= cp

CFLAG	=	-g3 -Wall -Wextra -luuid

SRC 	= 	src/main.c 								\
			src/send.c								\
			src/receive.c							\
			src/loop_client.c						\
			src/init_client_struct.c				\
			src/disconnect.c						\
			src/connect.c							\
			src/builtins/quit.c						\
			src/exec_command.c						\

OBJ	 = 	$(SRC:.c=.o)

LDLIBS = -lGL -lopenal -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAG) $(LDLIBS)
	$(CP) $(NAME) ../

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)
re: fclean all

.PHONY: all clean fclean re