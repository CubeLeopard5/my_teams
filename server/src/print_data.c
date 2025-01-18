#include "../../include/server/server.h"

void print_new_connection_data(int new_socket, server_t *server)
{
    printf(
        "New connection, socket fd is %d, ip is: %s, port: %d\n",
        new_socket,
        inet_ntoa(server->address.sin_addr),
        ntohs(server->address.sin_port)
    );
}

void print_disconnection(server_t *server)
{
    printf(
        "Host disconnected, ip: %s, port: %d\n",
        inet_ntoa(server->address.sin_addr),
        ntohs(server->address.sin_port)
    );
}