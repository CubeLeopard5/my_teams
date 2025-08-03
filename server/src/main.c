#include "../../include/server/server.h"

int main(int ac, char **av)
{
    server_t server;
    int result;

    handle_arguments(ac, av, &server);
    if (init_server_struct(&server, server.port) != 0) {
        return 84;
    }
    if (start_listening(&server) != 0) {
        return 84;
    }
    while ((result = loop_server(&server)) == 0) {

    }
    return (result > 0) ? 84 : 0;
}
