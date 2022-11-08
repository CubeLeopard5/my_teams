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
    if (dprintf(server->client_socket[client_nbr], "Loggin %s", uuid) < 0) {
        perror("Error when sending message\n");
        return 84;
    }
    return 0;
}

void login(server_t *server, size_t client_nbr, char **command)
{
    if (server->clients_data[client_nbr].is_logged == FALSE) {
        if (command[1]) {
            log_user(server, client_nbr, command[1]);
        } else {
            if (dprintf(server->client_socket[client_nbr], "No username provided\n") < 0) {
                perror("Error when sending message\n");
                return;
            }
        }
    } else {
        if (dprintf(server->client_socket[client_nbr],
        "Error user is alreay logged in\n") < 0) {
            perror("Error when sending message\n");
            return;
        }
    }
}
