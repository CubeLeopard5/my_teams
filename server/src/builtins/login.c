#include "../../../include/server/server.h"

char *create_uuid(void)
{
    uuid_t binuuid; //Generate a UUID for the client to identify him
    char *uuid = malloc(sizeof(char) * 40);

    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, uuid);
    return uuid;
}

int log_user(server_t *server, size_t client_nbr, char *username)
{
    char *uuid = create_uuid();

    server->clients_data[client_nbr].is_logged = TRUE;
    server->clients_data[client_nbr].username = strdup(username);
    server->clients_data[client_nbr].uuid =  strdup(uuid);
    server->clients_data[client_nbr].fd = client_nbr;
    send_message_to_client(server, client_nbr, uuid);
    return 0;
}

void login(server_t *server, size_t client_nbr, char **command)
{
    if (get_nb_word(command) != 2) {
        send_message_to_client(server, client_nbr, INVALID_ARGS_NUMBER);
        return;
    }
    if (server->clients_data[client_nbr].is_logged == FALSE) {
        log_user(server, client_nbr, command[1]);
    } else {
        send_message_to_client(server, client_nbr, "Error, user is alreay logged in");
    }
}
