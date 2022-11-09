#include "../../include/server/server.h"

int send_message_to_client(server_t *server, size_t client_nbr, char *msg)
{
    if (send(server->client_socket[client_nbr], msg, strlen(msg), 0) < 0) {
        perror("Unable to send message to client\n");
        return 84;
    }
    return 0;
}
