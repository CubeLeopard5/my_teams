#include "../../include/server/server.h"

int process_client_request_action(server_t *server, size_t i)
{
    char *buffer;
    char *cleaned_buffer;
    char **cmd;

    buffer = read_message_from_client(server->client_socket[i]);
    if (buffer == NULL) {
        if (disconnect_client(server, &server->client_socket[i]) != 0) {
            return 84;
        }
    } else {
        cleaned_buffer = remove_extra_spaces(buffer);
        cmd = str_to_word_tab(cleaned_buffer, " ");
        if (exec_command(server, i, cmd) == 84) {
            return 84;
        }
    }
    return 0;
}

int process_client_request(server_t *server)
{
    int result = 0;

    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (FD_ISSET(server->client_socket[i], &server->readfds)) {
            result = process_client_request_action(server, i);
            if (result != 0) {
                return 84;
            }
        }
    }
    return 0;
}