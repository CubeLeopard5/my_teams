#include "../../include/server/server.h"

void create_or_add_conv(server_t *server, int client_sender, int client_receiver) {
    printf("c1 = %s\nc2 = %s\n", find_client_by_index(server, client_sender), find_client_by_index(server, client_receiver));
}