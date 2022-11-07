#include "../../include/server/server.h"

void init_client_data(client_t *client)
{
    client->is_logged = FALSE;
    client->username = NULL;
    client->fd = -1;
    client->uuid = NULL;
}

int init_server_struct(server_t *server, int port)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
		server->client_socket[i] = 0;
        init_client_data(server->clients_data);
	}

    server->master_socket = socket(AF_INET , SOCK_STREAM , 0);
    if (server->master_socket == -1) {
		return 84;
	}

    server->address.sin_family = AF_INET;
	server->address.sin_addr.s_addr = INADDR_ANY;
	server->address.sin_port = htons(port);

	if (bind(server->master_socket, (struct sockaddr *)&server->address,
    sizeof(server->address)) < 0) {
		return 84;
	}
	printf("Listener on port %d \n", port);
    return 0;
}

int listening(server_t *server)
{
    if (listen(server->master_socket, MAX_CLIENTS) < 0) {
		return 84;
	}
    server->addrlen = sizeof(server->address);
    return 0;
}

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

int disconnect_client(server_t *server, int i)
{
    getpeername(server->client_socket[i], (struct sockaddr *)&server->address,
    (socklen_t*)&server->addrlen);
    printf("Host disconnected, ip: %s, port: %d\n",
    inet_ntoa(server->address.sin_addr), ntohs(server->address.sin_port));
    close(server->client_socket[i]);
    server->client_socket[i] = 0;
    return 0;
}

void send_pvt(server_t *server, size_t client_nbr, char **command)
{
    if (server->clients_data[client_nbr].is_logged == TRUE) {
        if (command[1]) {
            for (size_t i = 0; MAX_CLIENTS; i++) {
                if (server->clients_data[i].is_logged && strcmp(server->clients_data[i].uuid, command[1]) == 0) {
                    if (command[2]) {
                        dprintf(server->client_socket[i], command[2]);
                    }
                }
            }
        }
    }
}


void login(server_t *server, size_t client_nbr, char **command)
{
    uuid_t binuuid;
    char *uuid = malloc(sizeof(char) * 40);

    if (server->clients_data[client_nbr].is_logged == FALSE) {
        if (command[1]) {
            uuid_generate(binuuid);
            uuid_unparse_upper(binuuid, uuid);
            server->clients_data[client_nbr].is_logged = TRUE;
            server->clients_data[client_nbr].username = strdup(command[1]);
            server->clients_data[client_nbr].uuid =  strdup(uuid);
            dprintf(server->client_socket[client_nbr], "Loggin %s", uuid);
        } else {
            dprintf(server->client_socket[client_nbr], "Error PROUT\n");
        }
    } else {
        dprintf(server->client_socket[client_nbr],
        "Error 102 User is alreay logged in\n");
    }
}

int exec_command(server_t *server, size_t client_nbr, char **command)
{
    void (*builtins_functions[])(server_t *server, size_t client_nbr,
    char **command) = {&login, &send_pvt, NULL};

    if (command == NULL || command[0] == NULL)
        return 84;
    for (ssize_t i = 0; ALLOWED_COMMANDS[i] != NULL; i++) {
        if (strcmp(ALLOWED_COMMANDS[i], command[0]) == 0) {
            (*builtins_functions[i])(server, client_nbr, command);
            return i;
        }
    }
    return 84;
}

short is_valid_char(char c)
{
    return (c >= 'A' && c <= 'Z') ||
    (c >= 'a' && c <= 'z') ||
    (c >= '0' && c <= '9') ||
    (c == '.' || c == '/' || c == '-');
}

int nb_word(const char * str)
{
    int nb = 0;

    for (size_t i = 0; str[i];) {
        for (; str[i] && !is_valid_char(str[i]); i++);
        if (str[i])
            nb++;
        for (; str[i] && is_valid_char(str[i]); i++);
    }
    return nb + 1;
}

char **str_to_word_tab(char *str)
{
    int nb = nb_word(str);
    char **tab = malloc(sizeof(*tab) * nb);
    int j = 0;

    for (size_t i = 0; str[i];) {
        for (; str[i] && !is_valid_char(str[i]); i++)
            str[i] = '\0';
        if (str[i]) {
            tab[j] = &(str[i]);
            j++;
        }
        for (; str[i] && is_valid_char(str[i]); i++);
    }
    tab[j] = '\0';
    return tab;
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
                exec_command(server, i, str_to_word_tab(buffer));
                //dprintf(server->client_socket[i], buffer);
                //send(server->client_socket[i], buffer, strlen(buffer), 0);
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

int main(int ac , char **av)
{
    server_t server;
    int port = DEFAULT_PORT;

    if (ac == 2 && atoi(av[1]) > 0) {
        port = atoi(av[1]);
    }
    init_server_struct(&server, port);
    listening(&server);

    while(TRUE) {
        loop_server(&server);
    }		
	return 0;
}
