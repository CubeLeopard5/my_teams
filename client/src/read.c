#include "../../include/client/client.h"

void read_command(client_t *client)
{
    int len = 0;
    char buffer[MAX_LENGTH];

    len = recv(client->socket_fd, buffer, MAX_LENGTH - 1, 0);
    if (len < 0)
        printf("Error 420 recv error \n");
    buffer[len] = 0;
    if (!len) {
        end_client(client);
    }
    printf("message received = %s\n", buffer);
}