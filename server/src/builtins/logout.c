#include "../../../include/server/server.h"

int disconnect_client(server_t *server, int *fd)
{
    getpeername(*fd, (struct sockaddr *)&server->address,
    (socklen_t*)&server->addrlen);
    printf("Host disconnected, ip: %s, port: %d\n",
    inet_ntoa(server->address.sin_addr), ntohs(server->address.sin_port));
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
        send_message_to_client(server, client_nbr, "Invalid number of arguments");
    } else {
        send_message_to_client(server, client_nbr, "EXIT");
        disconnect_client(server, &server->client_socket[client_nbr]);
    }
}

void logout(server_t *server, size_t client_nbr, char **command)
{
    if (get_nb_word(command) != 1) {
        send_message_to_client(server, client_nbr, "Invalid number of arguments");
    } else if (server->clients_data[client_nbr].is_logged == TRUE) {
        init_client_data(&server->clients_data[client_nbr]);
    } else {
        send_message_to_client(server, client_nbr, "User not logged");
    }
}