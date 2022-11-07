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
        init_client_data(&server->clients_data[i]);
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