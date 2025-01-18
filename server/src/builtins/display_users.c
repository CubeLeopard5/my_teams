#include "../../../include/server/server.h"

void display_users(server_t *server, size_t client_nbr, char **command)
{
    if (get_nb_word(command) != 1) {
        send_message_to_client(server, client_nbr, ERR_INVALID_ARGS_NUMBER);
        return;
    }
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients_data[i].is_logged == TRUE) {
            dprintf(
                server->client_socket[client_nbr],
                "User %s with id = %s\n",
                server->clients_data[i].username,
                server->clients_data[i].uuid
            );
        }
    }
}