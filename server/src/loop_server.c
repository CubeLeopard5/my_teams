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
    return 0;
}

int accept_incomming_actions(server_t *server)
{
    if (select(server->max_sd + 1, &server->readfds, NULL, NULL, NULL) == -1) {
        return 84;
    }
    return 0;
}

int add_incomming_connection(server_t *server)
{
    int new_socket;

    if (FD_ISSET(server->master_socket, &server->readfds)) {
        new_socket = accept(server->master_socket,
        (struct sockaddr *)&server->address, (socklen_t*)&server->addrlen);
        if (new_socket < 0) {
            return 84;
        }
        printf("New connection, socket fd is %d, ip is: %s, port: %d\n",
        new_socket, inet_ntoa(server->address.sin_addr),
        ntohs(server->address.sin_port));
        for (size_t i = 0; i < MAX_CLIENTS; i++) {
            if (server->client_socket[i] == 0) {
                server->client_socket[i] = new_socket;
                printf("Adding to list of sockets as %d\n", i);   
                break;
            }
        }
    }
    return 0;
}

int input_output(server_t *server)
{
    char buffer[1025];
    int valread;

    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (FD_ISSET(server->client_socket[i], &server->readfds)) {
            valread = read(server->client_socket[i], buffer, 1024);
            if (valread == 0) {
                disconnect_client(server, i);
            } else {
                buffer[valread] = '\0';
                exec_command(server, i, str_to_word_tab(remove_extra_spaces(buffer), " "));
            }
        }
    }
    return 0;
}

int loop_server(server_t *server)
{
    get_max_socket_descriptor(server);
    accept_incomming_actions(server);
    add_incomming_connection(server);
    input_output(server);
    return 0;
}