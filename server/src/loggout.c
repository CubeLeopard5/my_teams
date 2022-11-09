#include "../../include/server/server.h"

int disconnect_client(server_t *server, int *fd)
{
    getpeername(*fd, (struct sockaddr *)&server->address,
    (socklen_t*)&server->addrlen);
    printf("Host disconnected, ip: %s, port: %d\n",
    inet_ntoa(server->address.sin_addr), ntohs(server->address.sin_port));
    if (close(*fd) == -1) {
        perror("Error while closing socket\n");
        return 84;
    }
    *fd = 0;
    return 0;
}