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
#define LENGTH 1024
#define LOGIN "LOGIN="
#define PASSWORD "PASSWORD="
#define UUID "UUID="

typedef struct reader_s
{
    FILE *file;
    DIR *d;
    struct dirent *dir;
    char *buffer;
}reader_t;

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

int send_message_to_client(server_t *server, size_t client_nbr, char *msg);
void login(server_t *server, size_t client_nbr, char **command);
void send_pvt(server_t *server, size_t client_nbr, char **command);
int listening(server_t *server);
int init_server_struct(server_t *server, int port);
char **str_to_word_tab(char *str, char *delim);
int exec_command(server_t *server, size_t client_nbr, char **command);
char *remove_extra_spaces(char *str);
int disconnect_client(server_t *server, int *fd);
int loop_server(server_t *server);
int get_nb_word(char **tab);
char *read_message_from_client(int fd);
void logout(server_t *server, size_t client_nbr, char **command);
void quit(server_t *server, size_t client_nbr, char **command);
void help(server_t *server, size_t client_nbr, char **command);
void display_users(server_t *server, size_t client_nbr, char **command);
void display_user(server_t *server, size_t client_nbr, char **command);
void display_conv(server_t *server, size_t client_nbr, char **command);
void init_client_data(client_t *client);
int find_client_by_uuid(server_t *server, char *uuid);
char *create_uuid(void);
char *find_client_by_index(server_t *server, int index);
void create_or_add_conv(server_t *server, int client_sender, int client_receiver, char *msg);
char *concat(char *str1, char *str2);
void create_dir(char *dir_name);
char *get_file_content(char *file_path);

#endif