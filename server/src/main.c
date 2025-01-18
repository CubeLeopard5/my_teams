#include "../../include/server/server.h"

int main(int ac, char **av)
{
    server_t server;

    handle_arguments(ac, av, &server);
    if (init_server_struct(&server, server.port) != 0) {
        return 84;
    }
    if (start_listening(&server) != 0) {
        return 84;
    }
    while(TRUE) {
        if (loop_server(&server) != 0) {
            return 84;
        }
    }
    return 0;
}
