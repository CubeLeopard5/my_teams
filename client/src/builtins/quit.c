#include "../../../include/client/client.h"

void quit(client_t *client, char *command)
{
    end_client(client);
    exit(0);
}