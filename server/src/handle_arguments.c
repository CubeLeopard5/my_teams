#include "../../include/server/server.h"

int is_there_port_arg(char * arg)
{
    if (strcmp(arg, "-p") == 0 || strcmp(arg, "--port") == 0) {
        return 1;
    }
    return 0;
}

int handle_arguments(int ac, char **av, server_t *server)
{
    server->port = DEFAULT_PORT;

    for (int i = 1; i < ac; i++) {
        if (is_there_port_arg(av[i]) == 1) {
            if (i + 1 < ac) {
                server->port = atoi(av[i + 1]);
                return 0;
            }
            perror("You didn't set the port number\n");
            return 84;
        }
    }
    return 0;
}