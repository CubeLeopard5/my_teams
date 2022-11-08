#include "../../include/client/client.h"

void end_client(client_t *client)
{
    if (client->is_logged == TRUE) {
        client->is_logged = FALSE;
        free(client->uuid);
        free(client->username);
    }
    close(client->socket_fd);
}