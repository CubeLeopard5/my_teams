#include "../../include/server/server.h"

int send_msg(server_t *server, size_t client_nbr, char *msg)
{
    if (send(server->client_socket[client_nbr], msg, strlen(msg), 0) < 0) {
        perror("Error when sending message\n");
        return 84;
    }
    return 0;
}

int find_client(server_t *server, char *command)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients_data[i].is_logged && strcmp(server->clients_data[i].uuid, command) == 0) {
            return i;
        }
    }
    return -1;
}

int get_nb_word(char **tab)
{
    int nb = 0;

    for (size_t i = 0; tab[i] != NULL; i++) {
        nb++;
    }
    return nb;
}

void send_pvt(server_t *server, size_t client_nbr, char **command)
{
    int nb_client = -1;

    if (get_nb_word(command) != 3) {
        send_msg(server, client_nbr, "No user uuid nor message provided\n");
        return;
    }
    if (server->clients_data[client_nbr].is_logged == TRUE) {
        nb_client = find_client(server, command[1]);
        if (nb_client != -1) {
            send_msg(server, nb_client, command[2]);
        }
    } else {
        send_msg(server, client_nbr, "You need to be logged before sending a message\n");
    }
}