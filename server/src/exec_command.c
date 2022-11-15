#include "../../include/server/server.h"

int exec_command(server_t *server, size_t client_nbr, char **command)
{
    void (*builtins_functions[])(server_t *server, size_t client_nbr,
    char **command) = {&login, &send_pvt, &logout, &quit, NULL};

    if (command == NULL || command[0] == NULL) {
        perror("No command entered\n");
        return 84;
    }

    for (size_t i = 0; ALLOWED_COMMANDS[i] != NULL; i++) {
        if (strcmp(ALLOWED_COMMANDS[i], command[0]) == 0) {
            (*builtins_functions[i])(server, client_nbr, command);
            return i;
        }
    }
    perror("No valid command found\n");
    return 84;
}