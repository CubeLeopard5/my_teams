#include "../../include/client/client.h"

int set_fd(client_t *client)
{
    FD_ZERO(&client->fds);
    FD_SET(STDIN_FILENO, &client->fds);
    FD_SET(client->socket_fd, &client->fds);
    if (select(client->socket_fd + 1, &client->fds, NULL, NULL, &client->tv) == -1) {
        perror("Unable to use select\n");
        return 84;
    }
    return 0;
}

int read_user_input(client_t *client)
{
    char buffer[MAX_LENGTH + 1];
    int rd;

    rd = read(STDIN_FILENO, buffer, MAX_LENGTH);
    if (rd == -1) {
        perror("Unable to read\n");
        return 84;
    } else if (rd == 0) { //Client asked for deconnection
        if (end_client(client) != 0) {
            return 84;
        }
    } else {
        buffer[rd] = '\0';
        if (send_message_to_server(client, buffer) != 0) {
            return 84;
        }
    }
    return 0;
}

int loop_client(client_t *client)
{
    if (set_fd(client) != 0) { //Reset the fd_set struct and use the select function
        return 84;
    }
    if (FD_ISSET(STDIN_FILENO, &client->fds)) { //Something has been rewritten on the standard input
        if (read_user_input(client) != 0) { //Read input content and send it to server
            return 84;
        }
    } else if (FD_ISSET(client->socket_fd, &client->fds)) { //Something has been received on our socket
        if (receive_server_message(client) != 0) { //Read message from server
            return 84;
        }
    }
    return 0;
}