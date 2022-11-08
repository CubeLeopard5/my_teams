#include "../../include/client/client.h"

int end_client(client_t *client)
{
    if (client->is_logged == TRUE) {
        client->is_logged = FALSE;
        free(client->uuid);
        free(client->username);
    }
    if (close(client->socket_fd) == -1) {
        perror("Error while closing socket\n");
        return 84;
    }
    return 0;
}