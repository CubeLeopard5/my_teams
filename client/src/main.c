#include "../../include/client/client.h"

void clear_buffers(client_t *client)
{
    memset(client->server_message,'\0',sizeof(client->server_message));
    memset(client->client_message,'\0',sizeof(client->client_message));
}

int init_struct_client(client_t *client, char *ip, int port)
{
    client->socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (client->socket_desc < 0) {
        return 84;
    }
    printf("Socket created successfully\n");

    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(port);
    client->server_addr.sin_addr.s_addr = inet_addr(ip);
    return 0;
}

int connect_to_server(client_t *client)
{
    if(connect(client->socket_desc, (struct sockaddr*)
    &client->server_addr, sizeof(client->server_addr)) < 0) {
        return 84;
    }
    printf("Connected with server successfully\n");
    return 0;
}

int get_client_input(client_t *client)
{
    printf("Enter message: ");
    if (fgets(client->client_message, MAX_LENGTH, stdin) == NULL) {
        return 84;
    }
    client->client_message[strcspn(client->client_message, "\n")] = 0;
    return 0;
}

int send_msg_to_server(client_t *client)
{
    if (send(client->socket_desc, client->client_message,
    strlen(client->client_message), 0) < 0) {
        return 84;
    }
    return 0;
}

int rcv_msg_from_server(client_t *client)
{
    if (recv(client->socket_desc, client->server_message,
    sizeof(client->server_message), 0) < 0) {
        return 84;
    }
    printf("Server's response: %s\n", client->server_message);
    return 84;
}

int loop_client(client_t *client)
{
    get_client_input(client);
    send_msg_to_server(client);
    rcv_msg_from_server(client);
    clear_buffers(client);
    return 0;
}

int main(int ac, char **av)
{
    client_t client;
    char *ip;
    int port;

    if (ac < 3 || atoi(av[1]) == 0 || atoi(av[2]) == 0) {
        return 84;
    }
    init_struct_client(&client, av[1], atoi(av[2]));
    clear_buffers(&client);
    connect_to_server(&client);

    while (TRUE) {
        loop_client(&client);
    }
    close(client.socket_desc);
    return 0;
}