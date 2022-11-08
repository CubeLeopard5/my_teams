#include "../../include/client/client.h"

int set_fd(client_t *client)
{
    FD_ZERO(&client->fds);
    FD_SET(STDIN_FILENO, &client->fds);
    FD_SET(client->socket_fd, &client->fds);
    if (select(client->socket_fd + 1, &client->fds, NULL, NULL, NULL) == -1) {
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
    } else if (rd == 0) {
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
    if (set_fd(client) != 0) {
        return 84;
    }
    if (FD_ISSET(STDIN_FILENO, &client->fds)) {
        if (read_user_input(client) != 0) {
            return 84;
        }
    } else if (FD_ISSET(client->socket_fd, &client->fds)) {
        if (receive_server_message(client) != 0) {
            return 84;
        }
    }
    return 0;
}