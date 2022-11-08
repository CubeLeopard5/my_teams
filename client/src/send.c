#include "../../include/client/client.h"

int send_message_to_server(client_t *client, char *msg)
{
    if (send(client->socket_fd, msg, strlen(msg), 0) < 0) {
        return 84;
    }
    return 0;
}
