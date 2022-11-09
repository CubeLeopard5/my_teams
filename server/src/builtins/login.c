#include "../../../include/server/server.h"

int log_user(server_t *server, size_t client_nbr, char *username)
{
    uuid_t binuuid;
    char uuid[40];

    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, uuid);
    server->clients_data[client_nbr].is_logged = TRUE;
    server->clients_data[client_nbr].username = strdup(username);
    server->clients_data[client_nbr].uuid =  strdup(uuid);
    send_message_to_client(server, client_nbr, uuid);
    return 0;
}

void login(server_t *server, size_t client_nbr, char **command)
{
    if (server->clients_data[client_nbr].is_logged == FALSE) {
        if (command[1]) {
            log_user(server, client_nbr, command[1]);
        } else {
            send_message_to_client(server, client_nbr, "No username provided\n");
        }
    } else {
        send_message_to_client(server, client_nbr, "Error user is alreay logged in\n");
    }
}
