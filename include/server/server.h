#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <uuid/uuid.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
	
#define TRUE 1
#define FALSE 0
#define DEFAULT_PORT 4000
#define MAX_CLIENTS 10
#define CONV_DIR "./convs/"
#define USERS_DIR "./users/"
#define MAX_MSG_LENGTH 1024
#define TEXT_FILE_EXT ".txt"
#define ERR_INVALID_ARGS_NUMBER "Error, invalid number of arguments"
#define ERR_USER_NOT_FOUND "Error, user not found"
#define ERR_NEED_TO_LOGGING_BEFORE_SENDING "Error, you need to be logged before sending a message"
#define ERR_ALREADY_LOGGED "Error, user is alreay logged in"
#define NO_CONVERSATION_FOUND "No conversation found"

typedef struct client_s
{
    short is_logged;
    char *username;
    char *uuid;
    size_t fd;
}client_t;

typedef struct server_s
{
    int port;
    struct sockaddr_in address;
    int master_socket;
    int client_socket[MAX_CLIENTS];
    fd_set readfds;
    int max_sd;
    int addrlen;
    client_t clients_data[MAX_CLIENTS];
}server_t;

static const char *ALLOWED_COMMANDS[] = {"/help", "/login", "/send", "/logout", "/quit", "/users", "/user", "/conv", NULL};

void create_dir(char *dir_name);
char *create_uuid(void);
void create_or_add_conv(server_t *server, int client_sender, int client_receiver, char *msg);
char *concat(char *str1, char *str2);
char *concat_all_messages(char **strs, size_t nb_begin, size_t nb_end);
int disconnect_client(server_t *server, int *fd);
void display_conv(server_t *server, size_t client_nbr, char **command);
void display_user(server_t *server, size_t client_nbr, char **command);
void display_users(server_t *server, size_t client_nbr, char **command);
int exec_command(server_t *server, size_t client_nbr, char **command);
int find_client_by_uuid(server_t *server, char *uuid);
char *find_client_by_index(server_t *server, int index);
char *get_file_content(char *file_path);
int get_length_of_all_messages(char **strs, size_t nb_begin, size_t nb_end);
int get_nb_word(char **tab);
int handle_arguments(int ac, char **av, server_t *server);
void help(server_t *server, size_t client_nbr, char **command);
int init_server_struct(server_t *server, int port);
void init_clients_data(client_t *client);
int is_there_port_arg(char *arg);
void login(server_t *server, size_t client_nbr, char **command);
void logout(server_t *server, size_t client_nbr, char **command);
int loop_server(server_t *server);
int process_client_request(server_t *server);
int process_client_request_action(server_t *server, size_t i);
void print_disconnection(server_t *server);
void print_new_connection_data(int new_socket, server_t *server);
void quit(server_t *server, size_t client_nbr, char **command);
char *remove_extra_spaces(char *str);
int send_message_to_client(server_t *server, size_t client_nbr, char *msg);
void send_pvt(server_t *server, size_t client_nbr, char **command);
int start_listening(server_t *server);
char **str_to_word_tab(char *str, char *delim);
char *read_message_from_client(int fd);


#endif