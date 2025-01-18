#ifndef CLIENT_H_
#define CLIENT_H_

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
	
#define TRUE 1
#define FALSE 0
#define MAX_LENGTH 1024

typedef struct client_s
{
    struct sockaddr_in server_addr;
    fd_set fds;
    char *uuid;
    char *username;
    int socket_fd;
    short is_logged;
    struct timeval tv;
}client_t;

static const char *ALLOWED_COMMANDS[] = {"quit", NULL};

int end_client(client_t *client);
int init_client_struct(client_t *client, char *ip, int port);
int loop_client(client_t *client);
int connect_to_server(client_t *client);
int send_message_to_server(client_t *client, char *msg);
int receive_server_message(client_t *client);
void quit(client_t *client, char *command);
int exec_command(client_t *client, char *command);

#endif