#include "../../../include/server/server.h"

void display_user(server_t *server, size_t client_nbr, char **command)
{
    int nb_client = -1;

    if (get_nb_word(command) != 2) {
        send_message_to_client(server, client_nbr, ERR_INVALID_ARGS_NUMBER);
        return;
    }
    nb_client = find_client_by_uuid(server, command[1]);
    if (nb_client != -1) {
        send_message_to_client(server, client_nbr, server->clients_data[nb_client].username);
    } else {
        send_message_to_client(server, client_nbr, ERR_USER_NOT_FOUND);
    }
}