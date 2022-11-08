#include "../../include/client/client.h"

int send_message_to_server(client_t *client, char *msg)
{
    if (send(client->socket_fd, msg, strlen(msg), 0) < 0) {
        perror("Unable to send message to server\n");
        return 84;
    }
    return 0;
}
