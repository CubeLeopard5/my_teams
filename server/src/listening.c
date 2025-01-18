#include "../../include/server/server.h"

int start_listening(server_t *server)
{
    int on = 1;
    int rc = 1;

    if (listen(server->master_socket, MAX_CLIENTS) < 0) {
        perror("Unable to listen\n");
		return 84;
	}
    server->addrlen = sizeof(server->address);
    rc = setsockopt(server->master_socket, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on));
    if (rc < 0) {
        perror("setsockopt() failed\n");
        close(server->master_socket);
        return 84;
    }
    printf("The server is now listening for connections\n");
    return 0;
}