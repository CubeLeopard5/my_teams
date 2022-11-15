#include "../../include/client/client.h"

int receive_server_message(client_t *client)
{
    int len = 0;
    char buffer[MAX_LENGTH];

    len = recv(client->socket_fd, buffer, MAX_LENGTH - 1, 0);
    if (len < 0) {
        perror("Error when receiving a message\n");
        return 84;
    }
    if (len == 0) {
        if (end_client(client) != 0) {
            return 84;
        }
        return 0;
    }
    buffer[len] = '\0';
    if (strcmp(buffer, "EXIT") == 0) {
        end_client(client);
        exit(0);
    } else {
        printf("message received = %s\n", buffer);
    }
    return 0;
}