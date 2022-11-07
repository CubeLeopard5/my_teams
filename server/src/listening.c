#include "../../include/server/server.h"

int listening(server_t *server)
{
    if (listen(server->master_socket, MAX_CLIENTS) < 0) {
		return 84;
	}
    server->addrlen = sizeof(server->address);
    return 0;
}