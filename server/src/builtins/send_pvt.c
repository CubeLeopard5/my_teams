#include "../../../include/server/server.h"

int get_length_of_all_messages(char **strs, size_t nb_begin, size_t nb_end)
{
    int nb = 0;

    for (size_t i = nb_begin; i < nb_end; i++) {
        nb += strlen(strs[i]);
    }
    return nb;
}

char *concat_all_messages(char **strs, size_t nb_begin, size_t nb_end)
{
    char *message = malloc(sizeof(char) * (get_nb_word(strs) +
    get_length_of_all_messages(strs, nb_begin, nb_end) + 1));
    int nb = 0;

    for (size_t i = nb_begin; i <= nb_end; i++) {
        for (size_t j = 0; strs[i][j] != '\0'; j++) {
            message[nb] = strs[i][j];
            nb++;
        }
        if (i < nb_end) {
            message[nb] = ' ';
            nb++;
        }
    }
    message[nb] = '\0';
    return message;
}

char *concat(char *str1, char *str2)
{
    char *rtn = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    int nb = 0;

    for (int i = 0; str1[i] != '\0'; i++, nb++) {
        rtn[nb] = str1[i];
    }
    for (int i = 0; str2[i] != '\0'; i++, nb++) {
        rtn[nb] = str2[i];
    }
    rtn[nb] = '\0';
    return rtn;
}

void send_pvt(server_t *server, size_t client_nbr, char **command)
{
    int nb_client = -1;
    char *msg = NULL;

    if (get_nb_word(command) < 3) {
        send_message_to_client(server, client_nbr, "Invalid number of arguments");
    } else if (server->clients_data[client_nbr].is_logged == TRUE) {
        nb_client = find_client_by_uuid(server, command[1]); //Use the UUID to find the client to send the message
        if (nb_client != -1) {
            msg = concat_all_messages(command, 2, get_nb_word(command) - 1);
            create_or_add_conv(server, client_nbr, nb_client, msg);
            send_message_to_client(server, nb_client, msg);
        } else {
            send_message_to_client(server, client_nbr, "User not found");
        }
    } else {
        send_message_to_client(server, client_nbr, "You need to be logged before sending a message");
    }
}