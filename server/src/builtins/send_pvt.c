#include "../../../include/server/server.h"

int find_client(server_t *server, char *command)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients_data[i].is_logged && strcmp(server->clients_data[i].uuid, command) == 0) {
            return i;
        }
    }
    return -1;
}

void send_pvt(server_t *server, size_t client_nbr, char **command)
{
    int nb_client = -1;

    if (get_nb_word(command) != 3) {
        send_message_to_client(server, client_nbr, "Invalid number of arguments");
        return;
    }
    if (server->clients_data[client_nbr].is_logged == TRUE) {
        nb_client = find_client(server, command[1]);
        if (nb_client != -1) {
            send_message_to_client(server, nb_client, command[2]);
        }
    } else {
        send_message_to_client(server, client_nbr, "You need to be logged before sending a message");
    }
}