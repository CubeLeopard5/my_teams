#include "../../../include/server/server.h"

void send_pvt(server_t *server, size_t client_nbr, char **command)
{
    int nb_client = -1;
    char *msg = NULL;

    if (get_nb_word(command) < 3) {
        send_message_to_client(server, client_nbr, ERR_INVALID_ARGS_NUMBER);
    } else if (server->clients_data[client_nbr].is_logged == TRUE) {
        nb_client = find_client_by_uuid(server, command[1]); //Use the UUID to find the client to send the message
        if (nb_client != -1) {
            msg = concat_all_messages(command, 2, get_nb_word(command) - 1);
            create_or_add_conv(server, client_nbr, nb_client, msg);
            send_message_to_client(server, nb_client, msg);
        } else {
            send_message_to_client(server, client_nbr, ERR_USER_NOT_FOUND);
        }
    } else {
        send_message_to_client(server, client_nbr, ERR_NEED_TO_LOGGING_BEFORE_SENDING);
    }
}