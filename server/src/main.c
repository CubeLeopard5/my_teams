#include "../../include/server/server.h"

short IS_RUNING = TRUE;

void crtl_handler(int sig)
{
    IS_RUNING = FALSE;
    printf("ctrl c\n");
}

void clear_buffers(server_t *server)
{
    memset(server->server_message, '\0', sizeof(server->server_message));
    memset(server->client_message, '\0', sizeof(server->client_message));
}

int init_server_struct(server_t *server)
{
    clear_buffers(server);

    server->socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (server->socket_desc == -1){
        printf("Error while creating socket\n");
        return 84;
    }
    printf("Socket created successfully\n");

    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(2000);
    server->server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server->socket_desc, (struct sockaddr *)&server->server_addr, sizeof(server->server_addr)) < 0){
        printf("Couldn't bind to the port\n");
        return 84;
    }
    printf("Done with binding\n");
    return 0;
}

int listening(server_t *server)
{
    if (listen(server->socket_desc, 1) < 0){
        printf("Error while listening\n");
        return 84;
    }
    printf("\nListening for incoming connections.....\n");
    return 0;
}

int accept_incomming_conncections(server_t *server)
{
    server->client_size = sizeof(server->client_addr);
    server->client_sock = accept(server->socket_desc, (struct sockaddr*)&server->client_addr, &server->client_size);
    
    if (server->client_sock < 0){
        printf("Can't accept\n");
        return 84;
    }
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(server->client_addr.sin_addr), ntohs(server->client_addr.sin_port));
    return 0;
}

int loop_server(server_t *server)
{
    if (recv(server->client_sock, server->client_message, sizeof(server->client_message), 0) < 0){
        printf("Couldn't receive\n");
        return 84;
    }
    printf("Msg from client: %s\n", server->client_message);
    
    // Respond to client:
    strcpy(server->server_message, "This is the server's message.");
    
    if (send(server->client_sock, server->server_message, strlen(server->server_message), 0) < 0){
        printf("Can't send\n");
        return 84;
    }
    clear_buffers(server);
    return 0;
}

int close_server(server_t *server)
{
    close(server->client_sock);
    close(server->socket_desc);
}

int main(void)
{
    server_t server;

    signal(SIGINT, crtl_handler);
    init_server_struct(&server);
    
    // Listen for clients:
    listening(&server);
    
    // Accept an incoming connection:
    accept_incomming_conncections(&server);
    
    // Receive client's message:
    while (1) {
        loop_server(&server);
        if (IS_RUNING == FALSE) {
            break;
        }
    }
    printf("A = %d", IS_RUNING);
    // Closing the socket:
    close_server(&server);
    
    return 0;
}