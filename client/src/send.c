#include "../../include/client/client.h"

int send_message_to_server(const client_t *client, const char *msg)
{
    if (send(client->socket_fd, msg, strlen(msg), 0) < 0) { //Send a message to the server
        perror("Unable to send message to server\n");
        return 84;
    }
    return 0;
}
