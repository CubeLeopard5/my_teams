#include "../../include/server/server.h"

int listening(server_t *server)
{
    if (listen(server->master_socket, MAX_CLIENTS) < 0) {
        perror("Unable to listen\n");
		return 84;
	}
    server->addrlen = sizeof(server->address);
    return 0;
}