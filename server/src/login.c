#include "../../include/server/server.h"

int log_user(server_t *server, size_t client_nbr, char *username)
{
    uuid_t binuuid;
    char uuid[40];

    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, uuid);
    server->clients_data[client_nbr].is_logged = TRUE;
    server->clients_data[client_nbr].username = strdup(username);
    server->clients_data[client_nbr].uuid =  strdup(uuid);
    dprintf(server->client_socket[client_nbr], "Loggin %s", uuid);
    return 0;
}

void login(server_t *server, size_t client_nbr, char **command)
{
    if (server->clients_data[client_nbr].is_logged == FALSE) {
        if (command[1]) {
            log_user(server, client_nbr, command[1]);
        } else {
            dprintf(server->client_socket[client_nbr], "Error PROUT\n");
        }
    } else {
        dprintf(server->client_socket[client_nbr],
        "Error 102 User is alreay logged in\n");
    }
}
