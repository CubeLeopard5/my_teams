#include "../../include/client/client.h"

int set_fd(client_t *client)
{
    FD_ZERO(&client->fds);
    FD_SET(STDIN_FILENO, &client->fds);
    FD_SET(client->socket_fd, &client->fds);
    if (select(client->socket_fd + 1, &client->fds, NULL, NULL, NULL) == -1)
        return 84;
    return 0;
}

int loop_client(client_t *client)
{
    char *buffer = malloc(sizeof(char) * MAX_LENGTH + 1);
    int rd;

    set_fd(client);
    if (FD_ISSET(STDIN_FILENO, &client->fds)) {
        rd = read(STDIN_FILENO, buffer, MAX_LENGTH);
        buffer[rd] = '\0';
        send_message_to_server(client, buffer);
    } else if (FD_ISSET(client->socket_fd, &client->fds)) {
        read_command(client);
    }
    return 0;
}