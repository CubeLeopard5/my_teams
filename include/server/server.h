#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
	
#define TRUE 1
#define FALSE 0
#define PORT 8888
#define MAX_CLIENTS 30

typedef struct server_s
{
    struct sockaddr_in address;
    int master_socket;
    int client_socket[MAX_CLIENTS];
    fd_set readfds;
    int max_sd;
    int addrlen;
}server_t;

#endif