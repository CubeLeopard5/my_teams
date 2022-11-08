#include "../../include/client/client.h"

int main(int ac, char **av)
{
    client_t client;
    char *ip;
    int port;

    if (ac < 3 || atoi(av[1]) == 0 || atoi(av[2]) == 0) {
        perror("Invalid arguments\n");
        return 84;
    }
    if (init_struct_client(&client, av[1], atoi(av[2])) != 0) {
        return 84;
    }
    if (connect_to_server(&client) != 0) {
        return 84;
    }
    while (TRUE) {
        if (loop_client(&client) != 0) {
            return 84;
        }
    }
    return 0;
}