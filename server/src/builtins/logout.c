#include "../../../include/server/server.h"

int disconnect_client(server_t *server, int *fd)
{
    getpeername(*fd, (struct sockaddr *)&server->address,
    (socklen_t*)&server->addrlen);
    print_disconnection(server);
    if (close(*fd) == -1) {
        perror("Error while closing socket\n");
        return 84;
    }
    *fd = 0;
    return 0;
}

void quit(server_t *server, size_t client_nbr, char **command)
{
    if (get_nb_word(command) != 1) {
        send_message_to_client(server, client_nbr, ERR_INVALID_ARGS_NUMBER);
    } else {
        send_message_to_client(server, client_nbr, "quit"); //Ask the client to disconnect
        disconnect_client(server, &server->client_socket[client_nbr]); //Close client socket on the server side
    }
}

void logout(server_t *server, size_t client_nbr, char **command)
{
    if (get_nb_word(command) != 1) {
        send_message_to_client(server, client_nbr, ERR_INVALID_ARGS_NUMBER);
    } else if (server->clients_data[client_nbr].is_logged == TRUE) {
        init_clients_data(&server->clients_data[client_nbr]); //Reset client struct
    } else {
        send_message_to_client(server, client_nbr, ERR_USER_NOT_FOUND);
    }
}