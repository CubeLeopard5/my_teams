#include "../../include/server/server.h"

int get_max_socket_descriptor(server_t *server)
{
    FD_ZERO(&server->readfds);
    FD_SET(server->master_socket, &server->readfds);
    server->max_sd = server->master_socket;

    for (size_t i = 0 ; i < MAX_CLIENTS; i++) {
        if (server->client_socket[i] > 0)
            FD_SET(server->client_socket[i], &server->readfds);
        if (server->client_socket[i] > server->max_sd)
            server->max_sd = server->client_socket[i];
    }
    return server->max_sd;
}

int accept_incomming_actions(server_t *server)
{
    if (select(server->max_sd + 1, &server->readfds, NULL, NULL, NULL) == -1) {
        perror("Unable to use select\n");
        return 84;
    }
    return 0;
}

int add_incomming_connection(server_t *server)
{
    int new_socket;

    if (FD_ISSET(server->master_socket, &server->readfds)) {
        new_socket = accept(server->master_socket,
        (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen);
        if (new_socket < 0) {
            perror("Unable to accept client\n");
            return 84;
        }
        print_new_connection_data(new_socket, server);
        for (size_t i = 0; i < MAX_CLIENTS; i++) {
            if (server->client_socket[i] == 0) {
                server->client_socket[i] = new_socket;
                printf("Adding to list of sockets as %d\n", i);   
                return 0;
            }
        }
    }
    return 0;
}

int process_client_request(server_t *server)
{
    char *buffer;
    char *cleaned_buffer;
    char **cmd;

    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (FD_ISSET(server->client_socket[i], &server->readfds)) {
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
        }
    }
    return 0;
}

int loop_server(server_t *server)
{
    get_max_socket_descriptor(server); //Reset the fd_set struct and search for the max fd in all sockets. Set the new value for fd_set struct
    if (accept_incomming_actions(server) != 0) {
        return 84;
    }
    if (add_incomming_connection(server) != 0) { //Check new client connection with accept function
        return 84;
    }
    if (process_client_request(server) != 0) { //Read client request and exec command for response
        return 84;
    }
    return 0;
}