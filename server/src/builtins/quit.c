#include "../../../include/server/server.h"

void quit(server_t *server, size_t client_nbr, char **command)
{
    if (get_nb_word(command) != 1) {
        send_message_to_client(server, client_nbr, ERR_INVALID_ARGS_NUMBER);
    } else {
        send_message_to_client(server, client_nbr, "quit"); //Ask the client to disconnect
        disconnect_client(server, &server->client_socket[client_nbr]); //Close client socket on the server side
    }
}