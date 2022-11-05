#ifndef CLIENT_H_
#define CLIENT_H_

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
#define MAX_LENGTH 2048

typedef struct client_s
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[MAX_LENGTH];
    char client_message[MAX_LENGTH];
}client_t;

#endif