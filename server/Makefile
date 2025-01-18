NAME    = myteams_server

CC		= gcc

CP  	= cp

CFLAG	=	-g3 -Wall -Wextra -luuid $(LIBS)

SRC 	= 	src/main.c 						\
			src/exec_command.c				\
			src/init_server_struct.c		\
			src/listening.c					\
			src/builtins/logout.c			\
			src/builtins/help.c				\
			src/builtins/display_users.c	\
			src/builtins/display_user.c		\
			src/builtins/login.c			\
			src/builtins/display_conv.c		\
			src/builtins/quit.c				\
			src/loop_server.c				\
			src/remove_extra_spaces.c		\
			src/send.c						\
			src/builtins/send_pvt.c			\
			src/str_to_word_tab.c			\
			src/get_nb_word.c				\
			src/read.c						\
			src/create_or_add_conv.c		\
			src/find_client.c				\
			src/manage_file.c				\
			src/print_data.c				\
			src/concat.c					\
			src/handle_arguments.c			\

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
