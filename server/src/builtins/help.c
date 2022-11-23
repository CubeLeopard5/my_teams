#include "../../../include/server/server.h"

void help(server_t *server, size_t client_nbr, char **command)
{
    char message[] = "Help:\nCommands available: /help, /login, /logout, /send, quit";

    if (get_nb_word(command) != 1) {
        send_message_to_client(server, client_nbr, "Invalid number of arguments");
        return;
    }
    send_message_to_client(server, client_nbr, message);
}