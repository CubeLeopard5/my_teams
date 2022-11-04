#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

typedef struct server_s
{
    int socket_desc;
    int client_sock;
    int client_size;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char server_message[2000];
    char client_message[2000];
}server_t;

#endif