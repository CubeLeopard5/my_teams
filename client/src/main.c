#include "../../include/client/client.h"

int main(int ac, char **av)
{
    client_t client;
    int result;

    if (ac != 3 || atoi(av[1]) == 0 || atoi(av[2]) == 0) {
        perror("Invalid arguments\n");
        return 84;
    }
    if (init_client_struct(&client, av[1], atoi(av[2])) != 0) {
        return 84;
    }
    if (connect_to_server(&client) != 0) {
        return 84;
    }
    while ((result = loop_client(&client)) == 0) {

    }
    return (result > 0) ? 84 : 0;
}