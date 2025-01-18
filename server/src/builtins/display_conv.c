#include "../../../include/server/server.h"

char *check_if_conv_exists(char *uuid1, char *uuid2) {
    char *file_name = concat(concat(concat(uuid1, "_"), uuid2), TEXT_FILE_EXT);
    char *path_file = concat(CONV_DIR, file_name);
    char *file_name_reversed = concat(concat(concat(uuid2, "_"), uuid1), TEXT_FILE_EXT);
    char *path_file_reversed = concat(CONV_DIR, file_name_reversed);

    if (access(path_file, F_OK) == 0) {
        return path_file;
    }  else if (access(path_file_reversed, F_OK) == 0) {
        return path_file_reversed;
    } else {
        return NULL;
    }
}

void display_conv(server_t *server, size_t client_nbr, char **command) {
    char *conv_file = NULL;

    if (get_nb_word(command) != 2) {
        send_message_to_client(server, client_nbr, ERR_INVALID_ARGS_NUMBER);
        return;
    } else if (server->clients_data[client_nbr].is_logged == TRUE) {
        conv_file = check_if_conv_exists(server->clients_data[client_nbr].uuid, command[1]);
        if (conv_file == NULL) {
            send_message_to_client(server, client_nbr, NO_CONVERSATION_FOUND);
        } else {
            send_message_to_client(server, client_nbr, get_file_content(conv_file));
        }
    } else {
        send_message_to_client(server, client_nbr, ERR_NEED_TO_LOGGING_BEFORE_SENDING);
    }
}