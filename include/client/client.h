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
    struct sockaddr_in server_addr;
    fd_set fds;
    char *uuid;
    char *username;
    int socket_fd;
    short is_logged;
}client_t;

void end_client(client_t *client);
int init_struct_client(client_t *client, char *ip, int port);
int loop_client(client_t *client);
int connect_to_server(client_t *client);
int send_message_to_server(client_t *client, char *msg);
void read_command(client_t *client);

#endif