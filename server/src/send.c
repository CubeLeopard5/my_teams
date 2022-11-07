#include "../../include/server/server.h"

void send_pvt(server_t *server, size_t client_nbr, char **command)
{
    if (server->clients_data[client_nbr].is_logged == TRUE && command[1]) {
        for (size_t i = 0; i < MAX_CLIENTS; i++) {
            if (server->clients_data[i].is_logged && strcmp(server->clients_data[i].uuid, command[1]) == 0 && command[2]) {
                send(server->client_socket[i], command[2], strlen(command[2]), 0);
                return;
            }
        }
    }
    send(server->client_socket[client_nbr], "Not found", strlen("Not found"), 0);
}
