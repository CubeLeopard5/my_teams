#include "../../../include/client/client.h"

void quit(client_t *client, [[maybe_unused]] const char *command)
{
    end_client(client);
    exit(0);
}