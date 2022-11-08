#include "../../include/server/server.h"

int main(int ac , char **av)
{
    server_t server;
    int port = DEFAULT_PORT;

    if (ac == 2 && atoi(av[1]) > 0) {
        port = atoi(av[1]);
    }
    if (init_server_struct(&server, port) != 0) {
        printf("Unable to init server structure");
        return 84;
    }
    if (listening(&server) != 0) {
        printf("Unable to listen");
        return 84;
    }
    while(TRUE) {
        if (loop_server(&server) != 0) {
            printf("Error in loop");
            return 84;
        }
    }
    return 0;
}
