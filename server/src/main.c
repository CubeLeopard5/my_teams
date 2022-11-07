#include "../../include/server/server.h"

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
