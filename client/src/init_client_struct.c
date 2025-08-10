#include "../../include/client/client.h"

int init_client_struct(client_t *client, const char *ip, int port)
{
    client->tv.tv_sec = 0;
    client->tv.tv_usec = 0;
    client->is_logged = FALSE;
    client->username = NULL;
    client->uuid = NULL;
    client->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->socket_fd < 0) {
        perror("Unable to create socket");
        return 84;
    }
    printf("Socket created successfully\n");

    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(port);
    client->server_addr.sin_addr.s_addr = inet_addr(ip);
    return 0;
}