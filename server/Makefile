NAME    = myteams_server

CC		= gcc

CP  	= cp

CFLAG	=	-g3 -Wall -Wextra -luuid

SRC 	= 	src/main.c 					\
			src/exec_command.c			\
			src/init.c					\
			src/listening.c				\
			src/builtins/logout.c		\
			src/builtins/login.c		\
			src/loop_server.c			\
			src/remove_extra_spaces.c	\
			src/send.c					\
			src/builtins/send_pvt.c		\
			src/str_to_word_tab.c		\
			src/get_nb_word.c			\
			src/read.c					\

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
