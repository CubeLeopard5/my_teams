#include "../../include/server/server.h"

int find_client_by_uuid(server_t *server, char *uuid)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients_data[i].is_logged &&
        strcmp(server->clients_data[i].uuid, uuid) == 0) {
            return i;
        }
    }
    return -1;
}

char *find_client_by_index(server_t *server, int index) {
    if (index >= MAX_CLIENTS) {
        return NULL;
    }
    if (server->clients_data[index].is_logged) {
        return server->clients_data[index].uuid;
    }
    return NULL;
}