#include "../../include/server/server.h"

char *get_conv_file_name(char *uuid_sender, char *uuid_receiver) {
    char *file_name = concat(concat(concat(uuid_sender, "_"), uuid_receiver), ".txt");
    char *path_file = concat(CONV_DIR, file_name);
    char *file_name_reversed = concat(concat(concat(uuid_receiver, "_"), uuid_sender), ".txt");
    char *path_file_reversed = concat(CONV_DIR, file_name_reversed);

    if (access(path_file_reversed, F_OK) == 0) {
        return path_file_reversed;
    } else {
        return path_file;
    }
}

void add_conv(char *file_path, char *msg) {
    FILE *fp;

    fp = fopen(file_path, "a+");
    fprintf(fp, concat(msg, ";\n"));
    fclose(fp);
}

void create_or_add_conv(server_t *server, int client_sender, int client_receiver, char *msg) {
    char *uuid_sender = find_client_by_index(server, client_sender);
    char *uuid_receiver = find_client_by_index(server, client_receiver);
    char *file_path = get_conv_file_name(uuid_sender, uuid_receiver);

    create_dir(CONV_DIR);
    add_conv(file_path, msg);
}