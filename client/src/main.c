#include "../../include/client/client.h"

int main(int ac, char **av)
{
    client_t client;
    char *ip;
    int port;

    if (ac < 3 || atoi(av[1]) == 0 || atoi(av[2]) == 0) {
        return 84;
    }
    init_struct_client(&client, av[1], atoi(av[2]));
    connect_to_server(&client);

    while (TRUE) {
        loop_client(&client);
    }
    return 0;
}