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
	
#define TRUE 1
#define FALSE 0
#define DEFAULT_PORT 4000
#define MAX_CLIENTS 10

typedef struct client_s
{
    short is_logged;
    char *username;
    char *uuid;
    int fd;
}client_t;

typedef struct server_s
{
    struct sockaddr_in address;
    int master_socket;
    int client_socket[MAX_CLIENTS];
    fd_set readfds;
    int max_sd;
    int addrlen;
    client_t clients_data[MAX_CLIENTS];
}server_t;

static const char *ALLOWED_COMMANDS[] = {"/login", "/send", NULL};

#endif