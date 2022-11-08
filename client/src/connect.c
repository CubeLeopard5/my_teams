#include "../../include/client/client.h"

int connect_to_server(client_t *client)
{
    if (connect(client->socket_fd, (struct sockaddr *)
    &client->server_addr, sizeof(client->server_addr)) < 0) {
        perror("Unable to connect to server\n");
        return 84;
    }
    printf("Connected with server successfully\n");
    return 0;
}