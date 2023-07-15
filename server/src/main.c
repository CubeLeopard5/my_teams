#include "../../include/server/server.h"

int handle_arguments(int ac, char **av, server_t *server)
{
    server->port = DEFAULT_PORT;

    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-p") == 0 || strcmp(av[i], "--port") == 0) {
            if (i + 1 < ac) {
                server->port = atoi(av[i + 1]);
            }
        }
    }
    return 0;
}

int main(int ac , char **av)
{
    server_t server;

    handle_arguments(ac, av, &server);
    if (init_server_struct(&server, server.port) != 0) {
        return 84;
    }
    if (listening(&server) != 0) {
        return 84;
    }
    while(TRUE) {
        if (loop_server(&server) != 0) {
            return 84;
        }
    }
    return 0;
}
