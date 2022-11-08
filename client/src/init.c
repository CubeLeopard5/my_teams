#include "../../include/client/client.h"

int init_struct_client(client_t *client, char *ip, int port)
{
    client->is_logged = FALSE;
    client->username = NULL;
    client->uuid = NULL;
    client->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->socket_fd < 0) {
        return 84;
    }
    printf("Socket created successfully\n");

    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(port);
    client->server_addr.sin_addr.s_addr = inet_addr(ip);
    return 0;
}