#include "../../../include/server/server.h"

int find_client(server_t *server, char *uuid)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients_data[i].is_logged &&
        strcmp(server->clients_data[i].uuid, uuid) == 0) {
            return i;
        }
    }
    return -1;
}

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

void create_dir(char *dir_name)
{
    struct stat st = {0};

    if (stat(dir_name, &st) == -1) {
        mkdir(dir_name, 0700);
    }
}

char *read_first_line_of_file(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, file);
    line[read - 1] = '\0';
    return line;
}

char *read_value_from_field(char *str)
{
    char *buffer = malloc(sizeof(char) * strlen(str));
    int i = 0;
    int j = 0;

    for (i; str[i] != '='; i++);
    i -= -1;
    for (i; str[i] != ';'; i++, j++) {
        buffer[j] = str[i];
    }
    buffer[j] = '\0';
    return buffer;
}

char *get_value_from_field(FILE *file, char *field)
{
    char *buffer = malloc(sizeof(char) * 1025);
    char *rtn = NULL;

    rewind(file);
    while (fgets(buffer, 1024, file)) {
        rtn = strstr(buffer, field);
        if (rtn != NULL) {
            return read_value_from_field(rtn);
        }
    }
    return NULL;
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

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');

    if (!dot || dot == filename) {
        return "";
    }
    return dot + 1;
}

FILE *get_conv()
{
    char uuid1[] = "a";
    char uuid2[] = "b";
    FILE *file = NULL;
    DIR *d = NULL;
    struct dirent *dir;
    char *buffer = NULL;

    create_dir(CONV_DIR);
    d = opendir(CONV_DIR);
    if (d == NULL) {
        perror("Conv directory not found\n");
    } else {
        while ((dir = readdir(d)) != NULL) {
            printf("A = %s\n", dir->d_name);
            if (strcmp(get_filename_ext(dir->d_name), "txt") == 0) {
                file = fopen(concat(CONV_DIR, dir->d_name), "a+");
                if (file == NULL) {
                    perror("Can't open file\n");
                } else {
                    printf("COUCOUC\n");
                    buffer = read_first_line_of_file(file);
                    printf("A = %s\n", buffer);
                    if (strcmp(buffer, concat(concat(uuid1, ":"), uuid2)) == 0) {
                        printf("GG\n");
                        int a = fprintf(file, "Bite");
                        printf("%d\n", a);
                    }
                }
                fclose(file);
            }
        }
        closedir(d);
    }
}

int check_if_user_exist(reader_t *reader, char *id)
{
    create_dir(USERS_DIR);
    reader->d = opendir(USERS_DIR);
    if (reader->d == NULL) {
        perror("Conv directory not found\n");
    } else {
        while ((reader->dir = readdir(reader->d)) != NULL) {
            if (strcmp(get_filename_ext(reader->dir->d_name), "txt") == 0) {
                reader->file = fopen(concat(USERS_DIR, reader->dir->d_name), "a+");
                if (reader->file == NULL) {
                    perror("Can't open file\n");
                } else {
                    char *password = get_value_from_field(reader->file, "PASSWORD=");
                    printf("A = %s\n", password);
                    char *login = get_value_from_field(reader->file, "LOGIN=");
                    printf("A = %s\n", login);
                }
                fclose(reader->file);
            }
        }
        closedir(reader->d);
    }
}

int create_user_file(char *username, char *password, char *uuid)
{
    FILE *file;

    file = fopen(concat(concat(USERS_DIR, create_uuid()), ".txt"), "a+");
    fprintf(file, concat(concat(LOGIN, username), ";\n"));
    fprintf(file, concat(concat(PASSWORD, password), ";\n"));
    fprintf(file, concat(concat(UUID, uuid), ";\n"));
}

void send_pvt(server_t *server, size_t client_nbr, char **command)
{
    int nb_client = -1;

    if (get_nb_word(command) < 3) {
        send_message_to_client(server, client_nbr, "Invalid number of arguments");
    } else if (server->clients_data[client_nbr].is_logged == TRUE) {
        nb_client = find_client(server, command[1]); //Use the UUID to find the client to send the message
        if (nb_client != -1) {
            send_message_to_client(server, nb_client, concat_all_messages(command, 2, get_nb_word(command) - 1));
        } else {
            send_message_to_client(server, client_nbr, "User not found");
        }
    } else {
        send_message_to_client(server, client_nbr, "You need to be logged before sending a message");
    }
}